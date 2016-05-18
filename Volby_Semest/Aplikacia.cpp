#include <iostream>

#include "Aplikacia.h"
#include "Parser.h"
#include "CmpStrany.h"
#include "CmpOkrskyOkres.h"

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
	okrsky_(new SortableTable<string, Okrsok*>(dalsia.okrsky_)),
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
	cout << "Nacitavanie vysledkov pre okrsky..." << endl;
	nacitajVysledkyPreOkrsky();
	cout << "Nacitavanie vysledkov o zapisanych volicoch..." << endl;
	nacitajZapisanychVolicov();
	cout << "Nacitavanie vysledkov o preferencnych hlasoch..." << endl;
	nacitajPreferenceHlasy();
	poNacitani();
}

void Aplikacia::nacitajVysledkyPreOkrsky()
{
	Parser parser("VyslPSOkrskySemColSep.txt");
	Okrsok* okrsok;
	Okres* okres;

	for (auto i(0); i < Parser::POCET_POL_STRAN; i++)
	{
		Strana* strana(new Strana(parser.dajNazovStrany(i)));
		strany_->insert(i + 1, strana);
	}

	while (parser.nacitajDalsiZaznam(';'))
	{
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
			okrsok->nastavAbsVyslStrany(strana->getData(), votesNum);
			celkovyPocetHlasov_ += votesNum;
		}
	}
}

void Aplikacia::nacitajZapisanychVolicov()
{
	Parser parser("ZapVoliciOkrskySemColSep.txt");

	for (auto item : *okrsky_)
	{
		parser.nacitajDalsiZaznam(';');
		item->getData()->nastavPocetZapVolicov(parser.dajIntDataNaPozicii(1));
	}
}

void Aplikacia::nacitajPreferenceHlasy()
{
	Parser parser("VyslPrednHlasOkrskyCSV.csv");

	for (auto item : *okrsky_)
	{
		parser.nacitajDalsiZaznam(',');
		for (auto strana : *strany_)
		{
			item->getData()->pridajPrefHlasy(strana->getData(),
				parser.dajIntDataNaPozicii(4 + (strana->getKey() - 1)));
		}
	}
}

void Aplikacia::vypisPolitickaStrana()
{
	cout << endl;
	cout << "Politicka strana" << endl;
	cout << "----------------" << endl;
	vypisZoznamPolStran();
	cout << "Zadajte cislo politickej strany:" << endl;
	int cisloStrany;
	cin >> cisloStrany;
	if (cisloStrany > 0 && cisloStrany < 27)
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

int Aplikacia::vyberOkres()
{
	cout << "Okres" << endl;
	cout << "-----" << endl;
	cout << "[ 1 ] Vyhladanie okresu" << endl;
	cout << "[ 2 ] Zoradenie okrskov daneho okresu" << endl;
	cout << "[ 3 ] Zoradenie vsetkych okrskov" << endl;
	celkovaVolba_ += 1;
	int volbaOkres;
	cin >> volbaOkres;
	return volbaOkres;
}

void Aplikacia::vyhladajOkres()
{
	cout << "Vyhladanie okresu" << endl;
	cout << "------------------" << endl;
	for (auto prvok : *okresy_ )
	{
		cout << "	" <<  prvok->getData()->dajNazov() << endl;
	}
	cout << "Zadajte okres:\n   >>> ";
	string okres;
	//cin >> okres;
	cin.ignore();
	getline(cin, okres);										
	(*okresy_)[okres]->vypisStatistiku();								//   Dorob vynimku
}

int Aplikacia::vyberZoradovanieOkres()
{
	cout << " Zoradenie okrskov daneho okresu" << endl;
	cout << "-------------------------------" << endl;
	cout << "[ 1 ] Podla poctu zapisanych volicov" << endl;
	cout << "[ 2 ] Podla relativneho vysledku danej politickej strany" << endl;
	cout << "[ 3 ] Podla absolutneho vysledku danej politickej strany" << endl;
	cout << "[ 4 ] Podla poctu preferencnych hlasov" << endl;
	int volbaZoradovania;
	cin >> volbaZoradovania;
	celkovaVolba_ += volbaZoradovania;
	return volbaZoradovania;
}

void Aplikacia::zoradPodlaVolicov()
{
	cout << "Zadajte okres:" << endl;
	string okres;
	cin >> okres;
	(*okresy_)[okres]->zoradOkrskyZapVolici();
	(*okresy_)[okres]->vypisOkrsky();
}

void Aplikacia::zoradPodlaRelVysl()
{
	cout << "Zadajte okres:" << endl;
	string okres;
	cin >> okres;
	cout << "Zadajte cislo politickej strany:" << endl;
	int cisloStrany;
	cin >> cisloStrany;
	Strana* strana((*strany_)[cisloStrany]);
	(*okresy_)[okres]->zoradOkrskyStranaRelVysledok(strana);
	(*okresy_)[okres]->vypisOkrsky();
}

void Aplikacia::zoradPodlaAbsVysl()
{
	cout << "Zadajte okres:" << endl;
	string okres;
	cin >> okres;
	cout << "Zadajte cislo politickej strany:" << endl;
	int cisloStrany;
	cin >> cisloStrany;
	Strana* strana((*strany_)[cisloStrany]);
	(*okresy_)[okres]->zoradOkrskyStranaAbsVysledok(strana);
	(*okresy_)[okres]->vypisOkrsky();
}

void Aplikacia::zoradPodlaPrefHlas()
{
	cout << "Zadajte okres:" << endl;
	string okres;
	cin >> okres;
	cout << "Zadajte cislo politickej strany:" << endl;
	int cisloStrany;
	cin >> cisloStrany;
	Strana* strana((*strany_)[cisloStrany]);
	(*okresy_)[okres]->zoradOkrskyPrefHlasy(strana);
	(*okresy_)[okres]->vypisOkrsky();
}

void Aplikacia::vypisZoznamPolStran()
{
	for (auto strana : *strany_)
	{
		cout << "       [ " << strana->getKey() << " ] " << strana->getData()->dajSkratku() << endl;
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
	cout << " MENU >> " << endl;
	cout << "[ 1 ] Vyhladanie politickej strany" << endl;
	cout << "[ 2 ] Vyhladanie okresu " << endl;
	cout << "[ 3 ] Zoradenie okrskou daneho okresu " << endl;
	cout << "[ 4 ] Zoradenie kandidatov " << endl;
	cout << "[ 5 ] Koniec " << endl;
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
			volbaZoradenia(vyberZoradovanieOkres());
			break;
		case 4:
			cout << " pracujem na tom " << endl;
			break;
		case 5:
			return 0;
		default:
			cout << "nic dalsie" << endl;
			break;
		}
	}
}

void Aplikacia::tretiaMoznost()
{

}

void Aplikacia::volbaZoradenia(int zorad)
{
	vypisZoznamPolStran();
	cout << "Zadajte cislo politickej strany:" << endl;
	int cisloStrany;
	cin >> cisloStrany;
	Strana* strana((*strany_)[cisloStrany]);
	if (zorad == 1) zoradOkrskyZapVolici();
	if (zorad == 2) zoradOkrskyStranaRelVysledok(strana);
	if (zorad == 3) zoradOkrskyStranaAbsVysledok(strana);
	if (zorad == 4)	zoradOkrskyPrefHlasy(strana);
	vypisOkrsky(strana,zorad);
	cout << endl;
}

void Aplikacia::vypisOkrsky(Strana* strana, int zorad)
{
	cout << "Zoznam okrskov : " << endl;
	for (auto okrsok : *okrsky_) {
		cout << okrsok->getData()->dajNazov() << " : ";
		if (zorad == 1) cout << okrsok->getData()->dajPocetZapVolici() << endl;
		if (zorad == 2) cout << okrsok->getData()->dajStranaRelVysl(strana) << endl;
		if (zorad == 3) cout << okrsok->getData()->dajStranaAbsVysl(strana) << endl;
		if (zorad == 4) cout << okrsok->getData()->dajStranaPrefHlasy(strana) << endl;
	}
}

void Aplikacia::zoradOkrskyZapVolici()
{
	CmpOkrskyZapVolici comparator;
	okrsky_->sort(comparator);
}

void Aplikacia::zoradOkrskyStranaRelVysledok(Strana * strana)
{
	CmpOkrskyStranaRelVysl comparator(strana);
	okrsky_->sort(comparator);
}

void Aplikacia::zoradOkrskyStranaAbsVysledok(Strana * strana)
{
	CmpOkrskyStranaAbsRes comparator(strana);
	okrsky_->sort(comparator);
}

void Aplikacia::zoradOkrskyPrefHlasy(Strana * strana)
{
	CmpOkrskyStranaPrefHlasy comparator(strana);
	okrsky_->sort(comparator);
}
