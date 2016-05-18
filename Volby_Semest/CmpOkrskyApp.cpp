#include "CmpOkrskyApp.h"

using namespace std;
using namespace DS;

CmpOkrskyApp::CmpOkrskyApp() :
	Comparator<string, Okrsok*>()
{
}

//  Abecedn� v�pis v�etk�ch okrskov v danom okrese.
int CmpOkrskyApp::compare(const TableItem<string, Okrsok*>& first,
	const TableItem<string, Okrsok*>& second) const
{
	if (first.getKey() > second.getKey())
		return 1;

	if (first.getKey() < second.getKey())
		return -1;

	if (first.getKey() == second.getKey())
		return 0;
}

