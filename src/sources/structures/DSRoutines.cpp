#include <stdexcept>
#include <string>


#include "DSRoutines.h"

using namespace std;
using namespace DS;

DSRoutines::DSRoutines()
{
}

bool DSRoutines::rangeCheck(const int index, const size_t size, bool throwException, const string* message)
{
	if (index >= 0 && (size_t)index < size)
		return true;
	else if (throwException)
		throw out_of_range(*message);
	else
		return false;
}
