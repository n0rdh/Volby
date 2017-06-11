#include "CmpOkrskyOkres.h"

using namespace std;
using namespace DS;

CmpOkrskyOkres::CmpOkrskyOkres() :
	Comparator<string, Okrsok*>()
{
}

int CmpOkrskyOkres::compare(const TableItem<string, Okrsok*>& first,
	const TableItem<string, Okrsok*>& second) const
{
	if (first.getKey() > second.getKey())
		return 1;

	if (first.getKey() < second.getKey())
		return -1;

	if (first.getKey() == second.getKey())
		return 0;
}