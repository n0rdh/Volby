#include "Strana.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace DS;

Strana::Strana(const string& nazov)	:
	celkovyVysledok_(0.0),
	hlasyStrany_(0),
	sucetVyslOkresu_(new TableSorted<Okres*, int*>(functionCompare)),
	sucetVyslKraje_(new TableSorted<string, int*>(functionCompare)),
	skratka_(nazov)
{
}

Strana::Strana(const Strana & dalsia) :
	celkovyVysledok_(dalsia.celkovyVysledok_),
	hlasyStrany_(dalsia.hlasyStrany_),
	sucetVyslOkresu_(new TableSorted<Okres*, int*>(*dalsia.sucetVyslOkresu_)),
	sucetVyslKraje_(new TableSorted<string, int*>(*dalsia.sucetVyslKraje_)),
	skratka_(dalsia.skratka_)
{
}

Strana::~Strana()
{
	delete sucetVyslKraje_;
	delete sucetVyslOkresu_;
}

Strana & Strana::operator=(const Strana & dalsia)
{
	if (this != &dalsia)
	{
		celkovyVysledok_ = dalsia.celkovyVysledok_;
		hlasyStrany_ = dalsia.hlasyStrany_;
		sucetVyslOkresu_ = dalsia.sucetVyslOkresu_;
		sucetVyslKraje_ = dalsia.sucetVyslKraje_;
	}
	return *this;
}

void Strana::vycisliCelkovyVysledok(int pocetVsetkychHlasov)
{
	(pocetVsetkychHlasov == 0) ? celkovyVysledok_ = 0 : celkovyVysledok_ = (static_cast<double>(hlasyStrany_) /
		static_cast<double>(pocetVsetkychHlasov)) * 100.0;
}

void Strana::pridajHlasyOkrsok(Okrsok* okrsok, int pocet)
{
	Okres* pomOkres = okrsok->dajOkres();
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

	cout << "Statistika :" << endl;
	cout << "    Celkovy volebny vysledok : " << setprecision(3) << celkovyVysledok_ << " %" << endl;
	cout << "    Najlepsi okres : " << najlepsiOkres->dajNazov() << " : " << *(*sucetVyslOkresu_)[najlepsiOkres] << endl;
	cout << "    Najhorsi okres : " << najhorsiOkres->dajNazov() << " : " << *(*sucetVyslOkresu_)[najhorsiOkres] << endl;
	cout << "    Najlepsi kraj : " << najlepsiKraj << " : " << *(*sucetVyslKraje_)[najlepsiKraj] << endl;
	cout << "    Najhorsi kraj: " << najhorsiKraj << " : " << *(*sucetVyslKraje_)[najhorsiKraj] << endl;
}

const string & Strana::dajSkratku()
{
	return skratka_;
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
