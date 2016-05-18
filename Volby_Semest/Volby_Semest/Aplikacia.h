#pragma once

#include "TableSorted.h"
#include "SortableTable.h"
#include "Strana.h"
#include "Okres.h"
#include "Okrsok.h"

class Aplikacia
{
public:
	Aplikacia();
	Aplikacia(const Aplikacia& dalsia);
	~Aplikacia();

	int spusti();
	Aplikacia& operator=(const Aplikacia& dalsia);

private:
	static const int KRAJ_POZ = 0;
	static const int OBVOD_POZ = 1;
	static const int OKRES_POZ = 2;
	static const int OKRSOK_POZ = 3;

	DS::TableSorted<int, Strana*>* strany_;
	DS::TableSorted<std::string, Okres*>* okresy_;
	DS::SortableTable<std::string, Okrsok*>* okrsky_;
	int celkovyPocetHlasov_;
	int celkovaVolba_;

	void volbaOkresuAVypis();
	void tretiaMoznost();
	void volbaZoradenia(int zorad);

	void nacitajSubory();
	void nacitajVysledkyPreOkrsky();
	void nacitajZapisanychVolicov();
	void nacitajPreferenceHlasy();

	void vypisPolitickaStrana();
	int  vyberOkres();
	void vyhladajOkres();
	int  vyberZoradovanieOkres();

	void zoradPodlaVolicov();
	void zoradPodlaRelVysl();
	void zoradPodlaAbsVysl();
	void zoradPodlaPrefHlas();

	void vypisZoznamPolStran();
	void poNacitani();
	void vypisHlavicku();
	void vypisMenu();

	void vypisOkrsky(Strana* strana, int zorad);
	void zoradOkrskyZapVolici();
	void zoradOkrskyStranaRelVysledok(Strana * strana);
	void zoradOkrskyStranaAbsVysledok(Strana * strana);
	void zoradOkrskyPrefHlasy(Strana * strana);

};

