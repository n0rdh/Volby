#include "CmpOkrskyApp.h"

using namespace std;
using namespace DS;

CmpOkrskyApp::CmpOkrskyApp() :
	Comparator<string, Okrsok*>()
{
}

//  Abecedný výpis všetkých okrskov v danom okrese.
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

