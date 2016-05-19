#include "Strana.h"
#include "CmpStrany.h"
#include "Parser.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace DS;

Strana::Strana(const string& nazov, int zaciatokKandidati, int koniecKandidati)	:
	celkovyVysledok_(0.0),
	hlasyStrany_(0),
	zaciatokKandidati_(zaciatokKandidati),
	koniecKandidati_(koniecKandidati),
	sucetVyslOkresu_(new TableSorted<Okres*, int*>(functionCompare)),
	sucetVyslKraje_(new TableSorted<string, int*>(functionCompare)),
	kandidatiUtriedeny_(new TableSorted<int, Kandidat*>(functionCompare)),
	kandidati_(new SortableTable<int, Kandidat*>()),
	skratka_(nazov)
{
	Parser parser("zoznamkandidatov.txt");
	string menoKandidta;
	for (int i(zaciatokKandidati); i <= koniecKandidati; i++)
	{
		menoKandidta =  parser.dajMenoKandidata(i);
		Kandidat * kandidat(new Kandidat(menoKandidta));
		kandidatiUtriedeny_->insert(i, kandidat);
	}							 	
	prelej();
}

Strana::Strana(const Strana & dalsia) :
	celkovyVysledok_(dalsia.celkovyVysledok_),
	hlasyStrany_(dalsia.hlasyStrany_),
	koniecKandidati_(dalsia.koniecKandidati_),
	zaciatokKandidati_(dalsia.zaciatokKandidati_),
	sucetVyslOkresu_(new TableSorted<Okres*, int*>(*dalsia.sucetVyslOkresu_)),
	sucetVyslKraje_(new TableSorted<string, int*>(*dalsia.sucetVyslKraje_)),
	kandidatiUtriedeny_(new TableSorted<int, Kandidat*>(*dalsia.kandidatiUtriedeny_)),
	kandidati_(new SortableTable<int, Kandidat*>(*dalsia.kandidati_)),
	skratka_(dalsia.skratka_)
{
}

Strana::~Strana()
{
	delete kandidatiUtriedeny_;
	delete sucetVyslKraje_;
	delete sucetVyslOkresu_;
	delete kandidati_;
}

Strana & Strana::operator=(const Strana & dalsia)
{
	if (this != &dalsia)
	{
		celkovyVysledok_ = dalsia.celkovyVysledok_;
		hlasyStrany_ = dalsia.hlasyStrany_;
		sucetVyslOkresu_ = dalsia.sucetVyslOkresu_;
		sucetVyslKraje_ = dalsia.sucetVyslKraje_;
		*kandidati_ = *dalsia.kandidati_;
		*kandidatiUtriedeny_ = *dalsia.kandidatiUtriedeny_;
	}
	return *this;
}

void Strana::pridajKandidatovyPrefHlasy(int index, Okrsok * okrsok, int pocetHlasov)
{
	(*kandidatiUtriedeny_)[index]->pridajOkrsokPrefHlasy(okrsok, pocetHlasov);
}

void Strana::vycisliCelkovyVysledok(int pocetVsetkychHlasov)
{
	(pocetVsetkychHlasov == 0) ? celkovyVysledok_ = 0 : celkovyVysledok_ = (static_cast<double>(hlasyStrany_) /
		static_cast<double>(pocetVsetkychHlasov)) * 100.0;
}

void Strana::pridajHlasyOkrsok(Okrsok* okrsok, int pocet)
{
	Okres* pomOkres(okrsok->dajOkres());
	int* hlasy;

	if (!sucetVyslOkresu_->tryFind(pomOkres, hlasy))
	{
		hlasy = new int(0);
		sucetVyslOkresu_->insert(pomOkres, hlasy);
	}
	*hlasy += pocet;
	const string& pomKraj(pomOkres->dajKraj());

	if (!sucetVyslKraje_->tryFind(pomKraj, hlasy))
	{
		hlasy = new int(0);
		sucetVyslKraje_->insert(pomKraj, hlasy);
	}
	*hlasy += pocet;
	hlasyStrany_ += pocet;
}

double Strana::dajCelkovyVysledok()
{
	return celkovyVysledok_;
}

void Strana::vypisStatistiku()
{
	string najlepsiKraj;
	string najhorsiKraj;
	najdiNajlepsiNajhorsiKraj(najlepsiKraj, najhorsiKraj);

	Okres* najlepsiOkres;
	Okres* najhorsiOkres;
	najdiNajlepsiNajhorsiOkres(najlepsiOkres,najhorsiOkres);

	cout << " Statistika :" << endl;
	cout << "    Celkovy volebny vysledok : " << setprecision(3) << celkovyVysledok_ << " %" << endl;
	cout << "    Najlepsi okres : " << najlepsiOkres->dajNazov() << setw(5) << *(*sucetVyslOkresu_)[najlepsiOkres] << endl;
	cout << "    Najhorsi okres : " << najhorsiOkres->dajNazov() << setw(5) << *(*sucetVyslOkresu_)[najhorsiOkres] << endl;
	cout << "    Najlepsi kraj : " << najlepsiKraj << setw(5) << *(*sucetVyslKraje_)[najlepsiKraj] << endl;
	cout << "    Najhorsi kraj: " << najhorsiKraj << setw(5) << *(*sucetVyslKraje_)[najhorsiKraj] << endl;
}

void Strana::vypisKandidatov(int vypis)
{
	cout << " Kandidati: " << endl;
	for (auto kandidat : *kandidati_)
	{
		cout << "	" << kandidat->getData()->dajMeno();
		if (vypis == 1) cout << " s najlepsim okrskom " << kandidat->getData()->dajOkrsokMaxPrefHlasyPocet();
		else if (vypis == 2 || vypis == 3) cout << "  " << kandidat->getData()->dajOkrsokMaxPrefHlasyPocet();
		cout << endl;
	}
}

const string & Strana::dajSkratku()
{
	return skratka_;
}

int Strana::dajZaciatokKandidati()
{
	return zaciatokKandidati_;
}

int Strana::dajKoniecKandidati()
{
	return koniecKandidati_;
}

void Strana::najdiNajlepsiNajhorsiOkres(Okres *& najlepsi, Okres *& najhorsi)
{ 
	int min = 500000;
	int max = 0;
	for (auto prvok : *sucetVyslOkresu_) 
	{ 
		if (*prvok->getData() > max) 
		{
			max = *prvok->getData();
			najlepsi = prvok->getKey();
		} 
		if (*prvok->getData() < min) 
		{
			min = *prvok->getData();
			najhorsi = prvok->getKey();
		}
	}
}

void Strana::najdiNajlepsiNajhorsiKraj(string & najlepsi, string & najhorsi)
{
	int min = 500000;
	int max = 0;
	for (auto prvok : *sucetVyslKraje_)
	{
		if (*prvok->getData() > max)
		{
			max = *prvok->getData();
			najlepsi = prvok->getKey();
		}
		if (*prvok->getData() < min)
		{
			min = *prvok->getData();
			najhorsi = prvok->getKey();
		}
	}
}

void Strana::zoradKandidatovAbecedne()
{
	CmpKandidatiAbecedne comparator;
	kandidati_->sort(comparator);
	for (auto kandidat : *kandidati_)
	{
		cout << " " << kandidat->getData()->dajMeno();
		cout << setw(20) << kandidat->getData()->dajOkrsokMaxPrefHlasyPocet()->dajNazov();
		cout << setw(25) << kandidat->getData()->dajMaxPocetHlasovOkrsok() << endl;
	}
}

void Strana::zoradKandidatovOkresPref(Okres* okres)
{
	CmpKandidatiOkresPrefHlasy comparator(okres);
	kandidati_->sort(comparator);
	for (auto kandidat : *kandidati_)
	{
		cout << " " << kandidat->getData()->dajMeno();
		cout << setw(20) << kandidat->getData()->dajPrefHlasyOkres(okres) << endl;
	}
}

void Strana::zoradKandidatovSKPref()
{
	CmpKandidatiSKPrefHlasy comparator;
	kandidati_->sort(comparator);
	for (auto kandidat : *kandidati_)
	{
		cout << " " << kandidat->getData()->dajMeno(); 
		cout << setw(20) << kandidat->getData()->dajPreferencneHlasyPocet() << endl;
	}
}

void Strana::prelej()
{	
	for (auto prvokKandidat : *kandidatiUtriedeny_)
	{
		kandidati_->insert(prvokKandidat->getKey(), prvokKandidat->getData());
	}
}
