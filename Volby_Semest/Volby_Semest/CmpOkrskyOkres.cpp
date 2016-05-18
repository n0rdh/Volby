#include "CmpOkrskyOkres.h"

using namespace std;
using namespace DS;

CmpOkrskyOkres::CmpOkrskyOkres() :
	Comparator<string, Okrsok*>()
{
}

/**
* Po�tu zap�san�ch voli�ov.
* Relat�vneho v�sledku danej politickej strany.
* Absol�tneho v�sledku danej politickej strany (teda ak� po�et, nie percent�, 
* platn�ch hlasov strana z�skala v okrsku).
* Po�tu preferen�n�ch hlasov, ktor� dostali spolu v�etci �lenovia zvolenej politickej strany.
**/

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