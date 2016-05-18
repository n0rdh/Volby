#include "Vysledok.h"

Vysledok::Vysledok() :
	absolutnyVysledok_(0),
	prefHlasy_(0),
	relativnyVysledok_(0.0)
{		
}

void Vysledok::vycisliRelativnyVysledok(int hlasyVsetkyStrany)
{
	(hlasyVsetkyStrany == 0) ? relativnyVysledok_ = 0.0 :
		relativnyVysledok_ = (static_cast<double>(absolutnyVysledok_) / hlasyVsetkyStrany) * 100.0;
}

void Vysledok::pridajPrefHlasy(int pocet)
{
	prefHlasy_ += pocet;
}

void Vysledok::nastavAbsolutnyVysledok(int pocetHlasov)
{
	absolutnyVysledok_ = pocetHlasov;
}

int Vysledok::dajAbsolutnyVysledok()
{
	return absolutnyVysledok_;
}

double Vysledok::dajRelativnyVysledok()
{
	return relativnyVysledok_;
}

int Vysledok::dajPrefHlasy()
{
	return prefHlasy_;
}
