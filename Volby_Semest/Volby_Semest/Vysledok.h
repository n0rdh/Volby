#pragma once
class Vysledok
{
public:
	Vysledok();
	void vycisliRelativnyVysledok(int hlasyVsetkyStrany);
	void pridajPrefHlasy(int pocet);

	void nastavAbsolutnyVysledok(int pocetHlasov);

	int dajAbsolutnyVysledok();
	double dajRelativnyVysledok();
	int dajPrefHlasy();

private:
	int absolutnyVysledok_;
	double relativnyVysledok_;
	int prefHlasy_;
};

