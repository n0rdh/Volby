#include "Comparator.h"
#include "Strana.h"
#include "Vysledok.h"


//####################################################################################################

class CmpKandidatiAbecedne :
	public DS::Comparator<int, Kandidat*>
{
public:
	CmpKandidatiAbecedne();

	virtual int compare(const DS::TableItem<int, Kandidat*>& first,
		const DS::TableItem<int, Kandidat*>& second) const override;
};


//####################################################################################################

class CmpKandidatiOkresPrefHlasy :
	public DS::Comparator<int, Kandidat*>
{
public:
	CmpKandidatiOkresPrefHlasy(Okres* okres);

	virtual int compare(const DS::TableItem<int, Kandidat*>& first,
		const DS::TableItem<int, Kandidat*>& second) const override;

private:
	Okres* okres_;
};
//####################################################################################################

class CmpKandidatiSKPrefHlasy :
	public DS::Comparator<int, Kandidat*>
{
public:
	CmpKandidatiSKPrefHlasy();

	virtual int compare(const DS::TableItem<int, Kandidat*>& first,
		const DS::TableItem<int, Kandidat*>& second) const override;
};

//####################################################################################################

class CmpStrany :
	public DS::Comparator<Strana*, Vysledok*>
{
public:
	CmpStrany();

	virtual int compare(const DS::TableItem<Strana*, Vysledok*>& first,
		const DS::TableItem<Strana*, Vysledok*>& second) const override;
};

class CmpOkrskyZapVolici :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyZapVolici();

	virtual int compare(const DS::TableItem<string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;
};

class CmpOkrskyStranaRelVysl :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyStranaRelVysl(Strana* strana);

	virtual int compare(const DS::TableItem<string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;

private:
	Strana* strana_;
};

class CmpOkrskyStranaAbsRes :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyStranaAbsRes(Strana* strana);

	virtual int compare(const DS::TableItem<std::string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;

private:
	Strana* strana_;
};

class CmpOkrskyStranaPrefHlasy :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyStranaPrefHlasy(Strana* strana);

	virtual int compare(const DS::TableItem<std::string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;

private:
	Strana* strana_;
};