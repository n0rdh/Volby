#pragma once
#include <string>
#include "SortableTable.h"
#include "Okrsok.h"
#include "Comparator.h"

class Okrsok;
class Strana;

class Okres
{
public:
	Okres(const std::string& obvod, const std::string& kraj,const std::string nazov);
	Okres(const Okres& dalsi);
	~Okres();

	Okres& operator=(const Okres& dalsi);

	void pridajOkrsok(const std::string& nazov, Okrsok* okrsok);
	void vypisStatistiku();
	void vypisOkrskyAbecedne();
	void vypisOkrsky();
	std::string vypis(std::string zaciatok, std::string koniec);

	void zoradOkrskyZapVolici();
	void zoradOkrskyStranaRelVysledok(Strana* strana);
	void zoradOkrskyStranaAbsVysledok(Strana* strana);
	void zoradOkrskyPrefHlasy(Strana* strana);

	const std::string& dajKraj();
	const std::string& dajNazov();

private:
	std::string nazov_;
	std::string volebnyObvod_;
	DS::SortableTable<string, Okrsok*>* okrsky_;
	std::string kraj_;
};

