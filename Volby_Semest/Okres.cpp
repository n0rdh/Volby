#include "Okres.h"
#include <iostream>
#include "CmpStrany.h"
#include "CmpOkrskyOkres.h"

using namespace DS;
using namespace std;

Okres::Okres(const string & obvod, const string & kraj, const string nazov) :
	volebnyObvod_(obvod),
	kraj_(kraj),
	okrsky_(new SortableTable<string, Okrsok*>()),
	nazov_(nazov)
{
}

Okres::Okres(const Okres & dalsi) :
	volebnyObvod_(dalsi.volebnyObvod_),
	kraj_(dalsi.kraj_),
	okrsky_(new SortableTable<string, Okrsok*>(*dalsi.okrsky_)),
	nazov_(dalsi.nazov_)
{
}

Okres::~Okres()
{
	delete okrsky_;
}

const string & Okres::dajKraj()
{
	return kraj_;
}

const string & Okres::dajNazov()
{
	return nazov_;
}

Okres & Okres::operator=(const Okres & dalsi)
{
	if (this != &dalsi) {
		volebnyObvod_ = dalsi.volebnyObvod_;
		kraj_ = dalsi.kraj_;
		*okrsky_ = *dalsi.okrsky_;
		nazov_ = dalsi.nazov_;
	} 
	return *this;
}

void Okres::pridajOkrsok(const string & nazov, Okrsok * okrsok)
{
	okrsky_->insert(nazov, okrsok);
}

void Okres::vypisStatistiku()
{
	cout << endl;
	cout << "	Statistika volebneho okresu : " << endl;
	cout << "	Prislusnost do volebneho obvodu: " << volebnyObvod_ << endl;
	cout << "	Prislusnost do kraja : " << kraj_ << endl;
	vypisOkrskyAbecedne();
}

void Okres::vypisOkrskyAbecedne()
{
	CmpOkrskyOkres comparator;
	okrsky_->sort(comparator);
	cout << "	Zoznam okrskov : " << endl;
	for (auto okrsok : *okrsky_) {
		cout << " " << okrsok->getData()->dajNazov() << endl;
		okrsok->getData()->vypisStranyOkrskuZoradene();
	} 
}

void Okres::vypisOkrsky()
{
	cout << "Zoznam okrskov : " << endl;
	for (auto okrsok : *okrsky_) {
		cout << okrsok->getData()->dajNazov() << endl;
	}
}

void Okres::zoradOkrskyZapVolici()
{
	CmpOkrskyZapVolici comparator;
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_) {
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajPocetZapisanychVolicov())) << endl;
	}
}

void Okres::zoradOkrskyStranaRelVysledok(Strana * strana)
{
	CmpOkrskyStranaRelVysl comparator(strana);
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajStranaRelativnehoVysl(strana))) << endl;
	}
}
 
void Okres::zoradOkrskyStranaAbsVysledok(Strana * strana)
{
	CmpOkrskyStranaAbsRes comparator(strana);
	okrsky_->sort(comparator);
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajStranaAbsolutnyVysl(strana))) << endl;
	}
}

void Okres::zoradOkrskyPrefHlasy(Strana * strana)
{
	CmpOkrskyStranaPrefHlasy comparator(strana);
	okrsky_->sort(comparator);
	for (auto okrsok : *okrsky_)
	{
		cout << vypis(okrsok->getData()->dajNazov(), to_string(okrsok->getData()->dajStranaPreferencneHlasy(strana))) << endl;
	}
}

std::string Okres::vypis(std::string zaciatok, std::string koniec)
{
	string vypis;
	vypis += zaciatok;
	for (int i(0); i < (40 - zaciatok.length()); i++)
	{
		vypis += " ";
	}
	vypis += koniec;
	return vypis;
}

