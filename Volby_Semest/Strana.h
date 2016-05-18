#pragma once

#include "Okres.h"
#include "Okrsok.h"
#include "Kandidat.h"
#include "TableSorted.h"
#include <string>

class Okres;
class Kandidat;
class Okrsok;

class Strana
{
public:
	Strana(const std::string& nazov);
	Strana(const Strana& dalsia);
	~Strana();
	Strana& operator=(const Strana& dalsia);

	void vycisliCelkovyVysledok(int pocetVsetkychHlasov);
	void pridajHlasyOkrsok(Okrsok* okrsok, int pocet);
	double dajCelkovyVysledok();
	void vypisStatistiku();
	void vypisKandidatov(int vypis);
	const std::string& dajSkratku();

	void zoradKandidatovAbecedne();
	void zoradKandidatovOkresPref(Okres* okres);
	void zoradKandidatovSKPref();

private:
	int hlasyStrany_;
	double celkovyVysledok_;
	std::string skratka_;

	DS::TableSorted<Okres*, int*>* sucetVyslOkresu_;
	DS::TableSorted<std::string, int*>* sucetVyslKraje_;
	DS::SortableTable<int, Kandidat*>* kandidati_;

	void najdiNajlepsiNajhorsiOkres(Okres*&  najlepsi, Okres*& najhorsi);
	void najdiNajlepsiNajhorsiKraj(std::string&  najlepsi, std::string& najhorsi);
};

