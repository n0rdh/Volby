#include <iostream>

#include "Aplikacia.h"
#include "Parser.h"
#include "CmpStrany.h"
#include "CmpOkrskyOkres.h"

#include <string>
#include <iomanip>

using namespace std;
using namespace DS;

Aplikacia::Aplikacia() :
	strany_(new TableSorted<int, Strana*>(functionCompare)),
	okresy_(new TableSorted<string, Okres*>(functionCompare)),
	okrsky_(new SortableTable<string, Okrsok*>),
	celkovyPocetHlasov_(0),
	celkovaVolba_(0)
{
}

Aplikacia::Aplikacia(const Aplikacia & dalsia) :
	strany_(new TableSorted<int, Strana*>(*dalsia.strany_)),
	okresy_(new TableSorted<string, Okres*>(*dalsia.okresy_)),
	okrsky_(new SortableTable<string, Okrsok*>(*dalsia.okrsky_)),
	celkovyPocetHlasov_(dalsia.celkovyPocetHlasov_),
	celkovaVolba_(dalsia.celkovaVolba_)
{
}

Aplikacia & Aplikacia::operator=(const Aplikacia & dalsia)
{
	if (this != &dalsia) {
		strany_ = dalsia.strany_;
		okresy_ = dalsia.okresy_;
		okrsky_ = dalsia.okrsky_;
		celkovyPocetHlasov_ = dalsia.celkovyPocetHlasov_;
		celkovaVolba_ = dalsia.celkovaVolba_;
	}
	return *this;
}

Aplikacia::~Aplikacia()
{
	delete strany_;
	delete okresy_;
	delete okrsky_;
}

void Aplikacia::nacitajSubory()
{
	cout << "Nacitavanie vysledkov pre okrsky";
	nacitajVysledkyPreOkrsky();
	cout << endl;
	cout << "Nacitavanie vysledkov o zapisanych volicoch" << endl;
	nacitajZapisanychVolicov();
	cout << "Nacitavam vysledky o preferencnych hlasoch" << endl;
	nacitajPreferenceHlasy();
	poNacitani();
}

void Aplikacia::nacitajVysledkyPreOkrsky()
{
	int rozsahyKandidatov[23][2] = {
		{ 0, 149 },
		{ 150, 298 },
		{ 299, 447 },
		{ 448, 480 },
		{ 481, 579 },
		{ 578, 728 },
		{ 729, 769 },
		{ 770, 859 },
		{ 860, 969 },
		{ 970, 1015 },
		{ 1016, 1163 },
		{ 1164, 1312 },
		{ 1313, 1461 },
		{ 1462, 1600 },
		{ 1601, 1749 },
		{ 1750, 1898 },
		{ 1899, 2047 },
		{ 2048, 2196 },
		{ 2197, 2344 },
		{ 2345, 2493 },
		{ 2494, 2642 },
		{ 2643, 2743 },
		{ 2744, 2892 }
	};

	Parser parser("VyslOkrsky.txt");
	Okrsok* okrsok;
	Okres* okres;
	double percenta(0.0), riadok(0.0);

	for (auto i(0); i < Parser::POCET_POL_STRAN; i++)
	{
		Strana* strana(new Strana(parser.dajNazovStrany(i), rozsahyKandidatov[i][0],rozsahyKandidatov[i][1]));
		strany_->insert(i + 1, strana);
	}

	while (parser.nacitajDalsiZaznam(';'))
	{
		//riadok++;
		//percenta = (riadok / 6000) * 100;
		//cout << "  Nacitavanie vysledkov pre okrsky" << setw(5) << (int)percenta + 1 << " %\r";
		if (!okresy_->tryFind(parser.dajStrDataNaPozicii(OKRES_POZ), okres))
		{
			okres = new Okres(parser.dajStrDataNaPozicii(OBVOD_POZ),
				parser.dajStrDataNaPozicii(KRAJ_POZ),
				parser.dajStrDataNaPozicii(OKRSOK_POZ));
			okresy_->insert(parser.dajStrDataNaPozicii(OKRES_POZ), okres);
		}

		const string& zoneName(parser.dajStrDataNaPozicii(OKRSOK_POZ));
		okrsok = new Okrsok(zoneName, okres);
		okrsky_->insert(zoneName, okrsok);
		okres->pridajOkrsok(parser.dajStrDataNaPozicii(OKRSOK_POZ), okrsok);

		for (auto strana : *strany_)
		{
			const int votesNum(parser.dajIntDataNaPozicii(4 + (strana->getKey() - 1)));

			strana->getData()->pridajHlasyOkrsok(okrsok, votesNum);
			okrsok->nastavAbsolutnyVyslStrany(strana->getData(), votesNum);
			celkovyPocetHlasov_ += votesNum;
		}
	}
}

void Aplikacia::nacitajZapisanychVolicov()
{
	Parser parser("ZapVolici.txt");
	double percenta(0.0), riadok(0.0);
	for (auto item : *okrsky_)
	{
		//riadok++;
		//percenta = (riadok / 6000) * 100;
		//cout << "  Nacitavanie vysledkov o zapisanych volicoch" << setw(5) << (int)percenta + 1 << " %\r";
		parser.nacitajDalsiZaznam(';');
		item->getData()->nastavPocetZapisanychVolicov(parser.dajIntDataNaPozicii(2));
	}
}

void Aplikacia::nacitajPreferenceHlasy()
{
	Parser parser("VyslPrednHlasOkr.csv");
	double percenta(0.0), riadok(0.0);
	for (auto prvokOkrsky : *okrsky_)
	{
		Okrsok * okrsok(prvokOkrsky->getData());
		//riadok++;
		//percenta = (riadok / 6000) * 100;
		//cout << "  Nacitanie vysledkov o kandidatoh" << setw(5) << (int)percenta + 1 << " %\r";
		parser.nacitajDalsiZaznam(',');
		for (auto prvokStrany : *strany_)
		{
			Strana* strana(prvokStrany->getData());
			int sumaPrefHlasovStrany(0);

			for (int i(strana->dajZaciatokKandidati()); i <= strana->dajKoniecKandidati(); i++)
			{
				int pocetHlasov(parser.dajIntDataNaPozicii(4 + i));
				strana->pridajKandidatovyPrefHlasy(i, okrsok, pocetHlasov);
				sumaPrefHlasovStrany += pocetHlasov;
			}

			okrsok->pridajPreferencnychHlasy(prvokStrany->getData(), sumaPrefHlasovStrany);
		}
	}
}

void Aplikacia::poNacitani()
{
	for (auto strana : *strany_)
	{
		strana->getData()->vycisliCelkovyVysledok(celkovyPocetHlasov_);
	}
	for (auto okrsok : *okrsky_)
	{
		okrsok->getData()->vycisliRelativneVysledky();
	}
}


void Aplikacia::vypisHlavicku()
{
	cout << " ------------------------------------------------------------------------------ " << endl;
	cout << "" << endl;
	cout << "               Spracovanie a analyza vysledkov volieb do NR SR 2016              " << endl;
	cout << "			    Tomas Illo (5ZI02B)							 " << endl;
	cout << "" << endl;
	cout << " ------------------------------------------------------------------------------ " << endl;
	cout << "" << endl;
}

void Aplikacia::vypisMenu()
{
	cout << "\n MENU >> " << endl;
	cout << "[ 1 ] Vyhladanie politickej strany" << endl;
	cout << "[ 2 ] Vyhladanie okresu " << endl;
	cout << "[ 3 ] Zoradenie okrskou  " << endl;
	cout << "[ 4 ] Zoradenie kandidatov " << endl;
	cout << "[ 5 ] Koniec \n   >>> ";
}

int Aplikacia::vyberZoradovanieOkres()
{
	system("cls");
	cout << " Zoradenie okrskov " << endl;
	cout << "-------------------------------" << endl;
	cout << "[ 1 ] Podla poctu zapisanych volicov" << endl;
	cout << "[ 2 ] Podla relativneho vysledku danej politickej strany" << endl;
	cout << "[ 3 ] Podla absolutneho vysledku danej politickej strany" << endl;
	cout << "[ 4 ] Podla poctu preferencnych hlasov\n   >>> ";
	int volbaZoradovania;
	cin >> volbaZoradovania;
	celkovaVolba_ += volbaZoradovania;
	return volbaZoradovania;
}

int Aplikacia::zoradenieKandidatovStrany()
{
	system("cls");
	cout << " Zoradenie kandidatov" << endl;
	cout << "-------------------------------" << endl;
	cout << "[ 1 ] Podla abecedy" << endl;
	cout << "[ 2 ] Podla poctu preferencnych hlasov v okrese" << endl;
	cout << "[ 3 ] Podla poctu preferencnych hlasov na Slovensku\n   >>> ";
	int volbaZoradovania;
	cin >> volbaZoradovania;
	celkovaVolba_ += volbaZoradovania;
	return volbaZoradovania;
}

int Aplikacia::vyberOkres()
{
	system("cls");
	cout << "Okres" << endl;
	cout << "-----" << endl;
	cout << "[ 1 ] Vyhladanie okresu" << endl;
	cout << "[ 2 ] Zoradenie okrskov daneho okresu" << endl;
	cout << "[ 3 ] Zoradenie vsetkych okrskov\n   >>> ";
	celkovaVolba_ += 1;
	int volbaOkres;
	cin >> volbaOkres;
	return volbaOkres;
}

void Aplikacia::vypisPolitickaStrana()
{
	system("cls");
	cout << "Politicka strana" << endl;
	cout << "----------------" << endl;
	vypisZoznamPolStran();
	cout << "Zadajte cislo politickej strany:\n   >>> ";
	int cisloStrany;
	cin >> cisloStrany;
	if (cisloStrany > 0 && cisloStrany < 24)
	{
		Strana* strana((*strany_)[cisloStrany]);
		cout << "Politicka strana  " << strana->dajSkratku() << "\n  ";
		strana->vypisStatistiku();
	}
	else
	{
		cout << "Taka strana neexistuje" << endl;
	}
	cout << endl;
}		

void Aplikacia::vypisZoznamPolStran()
{
	system("cls");
	cout << "Politicka strana" << endl;
	cout << "----------------" << endl;
	for (auto strana : *strany_)
	{
		cout << "       [ " << strana->getKey() << " ] " << strana->getData()->dajSkratku() << endl;
	}
}

void Aplikacia::vyhladajOkres()
{
	system("cls");
	cout << "Vyhladanie okresu" << endl;
	cout << "------------------" << endl;
	for (auto prvok : *okresy_)
	{
		cout << "	" << prvok->getData()->dajNazov() << endl;
	}
	cout << "Zadajte okres:\n   >>> ";
	string okres;
	cin.ignore();
	getline(cin, okres);
	//if (okresy_->tryFind(okres,))
	(*okresy_)[okres]->vypisStatistiku();
}

int Aplikacia::spusti()
{
	vypisHlavicku();
	nacitajSubory();
	int volba;
	while (true)
	{
		vypisMenu();
		cin >> volba;
		switch (volba)
		{
		case 1:
			vypisPolitickaStrana();
			break;
		case 2:
			vyhladajOkres();
			break;
		case 3:
			volbaZoradeniaOkrsok(vyberZoradovanieOkres());
			break;
		case 4:
			volbaStranyAOkresu(zoradenieKandidatovStrany());
			break;
		case 5:
			return 0;
		default:
			cout << "  Nespravna volba" << endl;
			break;
		}
	}
}

void Aplikacia::volbaStranyAOkresu(int zorad)
{
	system("cls");
	vypisZoznamPolStran();
	cout << "Zadajte cislo politickej strany:\n   >>> ";
	int cisloStrany;
	cin >> cisloStrany;
	Strana* strana((*strany_)[cisloStrany]);
	if (zorad == 1) strana->zoradKandidatovAbecedne();
	if (zorad == 2)
	{
		string okres;
		system("cls");
		cout << "Vyhladanie okresu" << endl;
		cout << "------------------" << endl;
		for (auto prvokOkresy : *okresy_) cout << "	" << prvokOkresy->getData()->dajNazov() << endl;
		cout << "Vyberte Okres: \n   >>> ";
		cin >> okres;
		strana->zoradKandidatovOkresPref((*okresy_)[okres]);
	}
	if (zorad == 3)	strana->zoradKandidatovSKPref();
	cout << endl;
}

void Aplikacia::volbaZoradeniaOkrsok(int zorad)
{
	system("cls");
	cout << "Volba vyhladavania" << endl;
	cout << "------------------" << endl;
	cout << "[ 1 ] Vyhladanie bez okresu" << endl;
	cout << "[ 2 ] Vyhladanie podla okresu\n   >>> ";
	int volba(0);
	int cisloStrany(0);
	cin >> volba;
	if (zorad != 1)
	{
		vypisZoznamPolStran();
		cout << "Zadajte cislo politickej strany:\n   >>> ";
		cin >> cisloStrany;
	}
	Strana* strana((*strany_)[cisloStrany]);
	if (volba == 1)
	{
		if (zorad == 1) zoradOkrskyZapVolici();
		if (zorad == 2) zoradOkrskyStranaRelVysledok(strana);
		if (zorad == 3) zoradOkrskyStranaAbsVysledok(strana);
		if (zorad == 4)	zoradOkrskyPrefHlasy(strana);
	}
	else
	{
		string okres;
		system("cls");
		cout << "Vyhladanie okresu" << endl;
		cout << "------------------" << endl;
		for (auto prvok : *okresy_) cout << "	" << prvok->getData()->dajNazov() << endl;
		cout << "Vyberte Okres\n   >>>  ";
		cin >> okres;
		//if (okresy_->tryFind(okres, (*okresy_)[okres]))

		if (zorad == 1) (*okresy_)[okres]->zoradOkrskyZapVolici();
		if (zorad == 2) (*okresy_)[okres]->zoradOkrskyStranaRelVysledok(strana);
		if (zorad == 3) (*okresy_)[okres]->zoradOkrskyStranaAbsVysledok(strana);
		if (zorad == 4)	(*okresy_)[okres]->zoradOkrskyPrefHlasy(strana);
	}
	cout << endl;
}

void Aplikacia::zoradOkrskyZapVolici()
{
	CmpOkrskyZapVolici comparator;
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajPocetZapisanychVolicov())) << endl;
	}
}

void Aplikacia::zoradOkrskyStranaRelVysledok(Strana * strana)
{
	CmpOkrskyStranaRelVysl comparator(strana);
	okrsky_->sort(comparator);
	string relativny;
	for (auto okrsok : *okrsky_)
	{
		double pom = okrsok->getData()->dajStranaRelativnehoVysl(strana);
		relativny = to_string(pom);
		cout << vypis(okrsok->getData()->dajNazov(), (pom < 10) ? relativny.substr(0, 4) : relativny.substr(0, 5)) << " %" << endl;
	}
}

void Aplikacia::zoradOkrskyStranaAbsVysledok(Strana * strana)
{
	CmpOkrskyStranaAbsRes comparator(strana);
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajStranaAbsolutnyVysl(strana))) << endl;
	}
}

void Aplikacia::zoradOkrskyPrefHlasy(Strana * strana)
{
	CmpOkrskyStranaPrefHlasy comparator(strana);
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajStranaPreferencneHlasy(strana))) << endl;
	}
}

string Aplikacia::vypis(std::string zaciatok, std::string koniec)
{
	string vypis("  ");
	vypis += zaciatok;
	for (int i(0); i < (40 - zaciatok.length()); i++)
	{
		vypis += " ";
	}
	vypis += koniec;
	return vypis;
}



