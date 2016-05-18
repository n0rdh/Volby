#include "CmpOkrskyOkres.h"

using namespace std;
using namespace DS;

CmpOkrskyOkres::CmpOkrskyOkres() :
	Comparator<string, Okrsok*>()
{
}

/**
* Poètu zapísaných volièov.
* Relatívneho výsledku danej politickej strany.
* Absolútneho výsledku danej politickej strany (teda aký poèet, nie percentá, 
* platných hlasov strana získala v okrsku).
* Poètu preferenèných hlasov, ktorý dostali spolu všetci èlenovia zvolenej politickej strany.
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