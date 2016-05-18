#include "Comparator.h"
#include "Strana.h"
#include "Vysledok.h"

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