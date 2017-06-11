#include "Comparator.h"

#include <string>
#include "Okrsok.h"

class CmpOkrskyOkres :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyOkres();

	virtual int compare(const DS::TableItem<std::string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;
};