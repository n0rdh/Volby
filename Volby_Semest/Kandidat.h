#pragma once
#include "Okrsok.h"
#include "TableSorted.h"
#include "Okres.h"
#include <string>
#include <iostream>

class Okrsok;
class Okres;

class Kandidat 
{
public:
	Kandidat(const std::string & meno);
	Kandidat(const Kandidat& dalsi);
	~Kandidat();

	Kandidat& operator=(const Kandidat& dalsi);

	void pridajOkrsokPrefHlasy(Okrsok* okrsok, int pocetHlasov);
	int dajPrefHlasyPocet();
	int dajPrefHlasyOkres(Okres * okres);
	Okrsok * dajOkrsokMaxPrefHlasyPocet();
	const string& dajMeno();

private:
	std::string meno_;
	int prefHlasyPocet_;
	int maxPocetHlasovOkrsok_;
	Okrsok* okrsok_;
	DS::TableSorted<Okres*, int>* okresHlasy_;
};
