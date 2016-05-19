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

	int dajPocetZapisanychVolicov();
	double dajStranaRelativnehoVysl(Strana* strana);
	int dajStranaAbsolutnyVysl(Strana* strana);
	int dajStranaPreferencneHlasy(Strana* strana);
	std::string dajNazov();
	Okres* dajOkres();

	void vypisStranyOkrskuZoradene();
	void vycisliRelativneVysledky();

	void nastavAbsolutnyVyslStrany(Strana* strana, int pocetHlasov);
	void nastavPocetZapisanychVolicov(int pocetVolicov);
	void pridajPreferencnychHlasy(Strana* strana, int dalsi);

private:
	DS::SortableTable<Strana*, Vysledok*>* strany_;
	int pocetZapVolici_;
	int pocetHlasovStran_;
	std::string nazov_;
	Okres* okres_;

};

