#pragma once
#include "SortableTable.h"
#include "Vysledok.h"
#include "Strana.h"
#include "Okres.h"
#include <string>

class Okres;
class Strana;

class Okrsok
{
public:
	Okrsok(std::string nazov, Okres* okres);
	Okrsok(const Okrsok& dalsi);
	~Okrsok();
	Okrsok& operator=(const Okrsok& dalsi);

	int dajPocetZapVolici();
	double dajStranaRelVysl(Strana* strana);
	int dajStranaAbsVysl(Strana* strana);
	int dajStranaPrefHlasy(Strana* strana);
	std::string dajNazov();
	Okres* dajOkres();
	void vypisStranyOkrskuZoradene();

	void vycisliRelativneVysledky();

	void nastavAbsVyslStrany(Strana* strana, int pocetHlasov);
	void nastavPocetZapVolicov(int pocetVolicov);
	void pridajPrefHlasy(Strana* strana, int dalsi);

private:
	DS::SortableTable<Strana*, Vysledok*>* strany_;
	int pocetZapVolici_;
	int pocetHlasovStran_;
	std::string nazov_;
	Okres* okres_;

};

