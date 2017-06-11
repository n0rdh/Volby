#pragma once

#include <string>

#include "Comparator.h"
#include "Okrsok.h"

class CmpOkrskyApp :
	public DS::Comparator<std::string, Okrsok*>
{
public:
	CmpOkrskyApp();

	virtual int compare(const DS::TableItem<std::string, Okrsok*>& first,
		const DS::TableItem<std::string, Okrsok*>& second) const override;
};
