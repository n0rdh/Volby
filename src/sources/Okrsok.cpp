#include "Okrsok.h"
#include "CmpStrany.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace DS;

Okrsok::Okrsok(string nazov, Okres* okres) :
	pocetHlasovStran_(0),
	pocetZapVolici_(0),
	strany_(new SortableTable<Strana*, Vysledok*>()),
	nazov_(nazov),
	okres_(okres)
{
}

Okrsok::Okrsok(const Okrsok & dalsi) :
	pocetHlasovStran_(dalsi.pocetHlasovStran_),
	pocetZapVolici_(dalsi.pocetZapVolici_),
	strany_(new SortableTable<Strana*, Vysledok*>(*dalsi.strany_)),
	nazov_(dalsi.nazov_),
	okres_(dalsi.okres_)
{
}

Okrsok::~Okrsok()
{
	delete strany_;
}

Okrsok & Okrsok::operator=(const Okrsok & dalsi)
{
	if (this != &dalsi) 
	{
		delete strany_;
		pocetHlasovStran_ = dalsi.pocetHlasovStran_;
		pocetZapVolici_ = dalsi.pocetZapVolici_;
		*strany_ = *dalsi.strany_;
		nazov_ = dalsi.nazov_;
		okres_ = dalsi.okres_;
	}
	return *this;
}

void Okrsok::pridajPreferencnychHlasy(Strana * strana, int pocHlasov)
{
	(*strany_)[strana]->pridajPrefHlasy(pocHlasov);
}

int Okrsok::dajPocetZapisanychVolicov()
{
	return pocetZapVolici_;
}

double Okrsok::dajStranaRelativnehoVysl(Strana * strana)
{
	return (*strany_)[strana]->dajRelativnyVysledok();
}

int Okrsok::dajStranaAbsolutnyVysl(Strana * strana)
{
	return (*strany_)[strana]->dajAbsolutnyVysledok();
}

int Okrsok::dajStranaPreferencneHlasy(Strana * strana)
{
	return (*strany_)[strana]->dajPrefHlasy();
}

string Okrsok::dajNazov()
{
	return nazov_;
}

Okres * Okrsok::dajOkres()
{
	return okres_;
}

void Okrsok::vypisStranyOkrskuZoradene()
{
	CmpStrany comparator;
	strany_->sort(comparator);
	cout << " --------------------------------" << endl;
	cout << "    Politicke strany   " << endl;
	for (auto strana: *strany_)
	{
		cout << "	" << left << setw(52) << strana->getKey()->dajSkratku() 
				<< strana->getData()->dajRelativnyVysledok() << " %" << endl;
	}
	cout << " --------------------------------" << endl;
}

void Okrsok::vycisliRelativneVysledky()
{
	for (auto prvok : *strany_)
	{
		prvok->getData()->vycisliRelativnyVysledok(pocetHlasovStran_);
	}
}

void Okrsok::nastavAbsolutnyVyslStrany(Strana * strana, int pocetHlasov)
{
	pocetHlasovStran_ += pocetHlasov;
	Vysledok* pomVys;

	if (!strany_->tryFind(strana, pomVys))
	{
		pomVys = new Vysledok();
		strany_->insert(strana, pomVys);
	}
	pomVys->nastavAbsolutnyVysledok(pocetHlasov);
}

void Okrsok::nastavPocetZapisanychVolicov(int pocetVolicov)
{
	pocetZapVolici_ = pocetVolicov;
}
