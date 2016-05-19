#include "CmpStrany.h"

using namespace std;
using namespace DS;

CmpStrany::CmpStrany() :
	Comparator<Strana*, Vysledok*>()
{
}

int CmpStrany::compare(const TableItem<Strana*, Vysledok*>& first,
	const TableItem<Strana*, Vysledok*>& second) const
{
	const double rozdiel(first.getData()->dajRelativnyVysledok() - second.getData()->dajRelativnyVysledok());
	if (rozdiel > 0.0)
	{
		return 1;
	}
	else if (rozdiel < 0.0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//####################################################################################################

CmpKandidatiAbecedne::CmpKandidatiAbecedne() :
	Comparator<int, Kandidat*>()
{
}

int CmpKandidatiAbecedne::compare(const TableItem<int, Kandidat*>& first,
	const TableItem<int, Kandidat*>& second) const
{
	return first.getData()->dajMeno().compare(second.getData()->dajMeno());
}

//####################################################################################################

CmpKandidatiSKPrefHlasy::CmpKandidatiSKPrefHlasy() :
	Comparator<int, Kandidat*>()
{
}

int CmpKandidatiSKPrefHlasy::compare(const TableItem<int, Kandidat*>& first,
	const TableItem<int, Kandidat*>& second) const
{
	return first.getData()->dajPreferencneHlasyPocet() -
		second.getData()->dajPreferencneHlasyPocet();
}

//####################################################################################################

CmpKandidatiOkresPrefHlasy::CmpKandidatiOkresPrefHlasy(Okres* okres) :
	okres_(okres)
{
}

int CmpKandidatiOkresPrefHlasy::compare(const DS::TableItem<int, Kandidat*>& first,
	const DS::TableItem<int, Kandidat*>& second) const
{
	return first.getData()->dajPreferencneHlasyOkres(okres_) - second.getData()->dajPreferencneHlasyOkres(okres_);
}

//####################################################################################################


CmpOkrskyZapVolici::CmpOkrskyZapVolici() :
	Comparator<string, Okrsok*>()
{
}

int CmpOkrskyZapVolici::compare(const DS::TableItem<string, Okrsok*>& first,
	const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajPocetZapisanychVolicov() - second.getData()->dajPocetZapisanychVolicov();
}

CmpOkrskyStranaRelVysl::CmpOkrskyStranaRelVysl(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaRelVysl::compare(const DS::TableItem<string, Okrsok*>& first, const DS::TableItem<string, Okrsok*>& second) const
{
	const double rozdiel(first.getData()->dajStranaRelativnehoVysl(strana_) - second.getData()->dajStranaRelativnehoVysl(strana_));
	if (rozdiel > 0.0)
	{
		return 1;
	}
	else if (rozdiel < 0.0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

CmpOkrskyStranaAbsRes::CmpOkrskyStranaAbsRes(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaAbsRes::compare(const DS::TableItem<string, Okrsok*>& first,
	const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajStranaAbsolutnyVysl(strana_) - second.getData()->dajStranaAbsolutnyVysl(strana_);
}

CmpOkrskyStranaPrefHlasy::CmpOkrskyStranaPrefHlasy(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaPrefHlasy::compare(const DS::TableItem<string, Okrsok*>& first, const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajStranaPreferencneHlasy(strana_) - second.getData()->dajStranaPreferencneHlasy(strana_);
}
