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
	return first.getData()->dajRelativnyVysledok() - second.getData()->dajRelativnyVysledok();
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
	return first.getData()->dajOkrsokMaxPrefHlasyPocet() -
		second.getData()->dajOkrsokMaxPrefHlasyPocet();
}

//####################################################################################################

CmpKandidatiOkresPrefHlasy::CmpKandidatiOkresPrefHlasy(Okres* okres) :
	okres_(okres)
{
}

int CmpKandidatiOkresPrefHlasy::compare(const DS::TableItem<int, Kandidat*>& first,
	const DS::TableItem<int, Kandidat*>& second) const
{
	return 0;
}

//####################################################################################################







//Pre každý okrsok vypísané politické strany v poradí pod¾a ich relatívneho
//volebného výsledku (teda ko¾ko percent platných hlasov strana získala) 
//v tomto okrsku (tento volebný výsledok pre každú stranu aj uveïte).


CmpOkrskyZapVolici::CmpOkrskyZapVolici() :
	Comparator<string, Okrsok*>()
{
}

int CmpOkrskyZapVolici::compare(const DS::TableItem<string, Okrsok*>& first,
	const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajPocetZapVolici() - second.getData()->dajPocetZapVolici();
}

CmpOkrskyStranaRelVysl::CmpOkrskyStranaRelVysl(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaRelVysl::compare(const DS::TableItem<string, Okrsok*>& first, const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajStranaRelVysl(strana_) - second.getData()->dajStranaRelVysl(strana_);
}

CmpOkrskyStranaAbsRes::CmpOkrskyStranaAbsRes(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaAbsRes::compare(const DS::TableItem<string, Okrsok*>& first,
	const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajStranaAbsVysl(strana_) - second.getData()->dajStranaAbsVysl(strana_);
}

CmpOkrskyStranaPrefHlasy::CmpOkrskyStranaPrefHlasy(Strana * strana) :
	Comparator<string, Okrsok*>(),
	strana_(strana)
{
}

int CmpOkrskyStranaPrefHlasy::compare(const DS::TableItem<string, Okrsok*>& first, const DS::TableItem<string, Okrsok*>& second) const
{
	return first.getData()->dajStranaPrefHlasy(strana_) - second.getData()->dajStranaPrefHlasy(strana_);
}
