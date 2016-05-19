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
	Strana(const std::string& nazov, int zaciatokKandidati, int koniecKandidati);
	Strana(const Strana& dalsia);
	~Strana();
	Strana& operator=(const Strana& dalsia);

	void pridajKandidatovyPrefHlasy(int index, Okrsok* okrsok, int pocetHlasov);
	void pridajHlasyOkrsok(Okrsok* okrsok, int pocet);

	void vycisliCelkovyVysledok(int pocetVsetkychHlasov);
	void vypisStatistiku();
	void vypisKandidatov(int vypis);

	const std::string& dajSkratku();
	int dajZaciatokKandidati();
	int dajKoniecKandidati();
	double dajCelkovyVysledok();

	void zoradKandidatovAbecedne();
	void zoradKandidatovOkresPref(Okres* okres);
	void zoradKandidatovSKPref();

private:
	int hlasyStrany_;
	int zaciatokKandidati_;
	int koniecKandidati_;
	double celkovyVysledok_;
	std::string skratka_;

	DS::TableSorted<Okres*, int*>* sucetVyslOkresu_;
	DS::TableSorted<std::string, int*>* sucetVyslKraje_;
	DS::TableSorted<int, Kandidat*>* kandidatiUtriedeny_;
	DS::SortableTable<int, Kandidat*>* kandidati_;

	void prelej();
	void najdiNajlepsiNajhorsiOkres(Okres*&  najlepsi, Okres*& najhorsi);
	void najdiNajlepsiNajhorsiKraj(std::string&  najlepsi, std::string& najhorsi);
};

