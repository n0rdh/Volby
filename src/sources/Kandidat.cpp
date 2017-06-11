#include "Kandidat.h"

using namespace std;
using namespace DS;

Kandidat::Kandidat(const string & meno)	:
	meno_(meno),
	prefHlasyPocet_(0),
	maxPocetHlasovOkrsok_(0),
	okrsok_(nullptr),
	okresHlasy_(new TableSorted<Okres*, int*>(functionCompare))
{
}

Kandidat::Kandidat(const Kandidat& dalsi) :
	meno_(dalsi.meno_),
	prefHlasyPocet_(dalsi.prefHlasyPocet_),
	maxPocetHlasovOkrsok_(dalsi.maxPocetHlasovOkrsok_),
	okrsok_(dalsi.okrsok_),
	okresHlasy_(new TableSorted<Okres*, int*>(*dalsi.okresHlasy_))
{
}

Kandidat& Kandidat::operator=(const Kandidat& dalsi)
{
	if (this != &dalsi)
	{
		meno_ = dalsi.meno_;
		prefHlasyPocet_ = dalsi.prefHlasyPocet_;
		maxPocetHlasovOkrsok_ = dalsi.maxPocetHlasovOkrsok_;
		okrsok_ = dalsi.okrsok_;
		okresHlasy_ = dalsi.okresHlasy_;
	}
	return *this;
}

Kandidat::~Kandidat()
{
	delete okresHlasy_;
}

void Kandidat::pridajOkrsokPrefHlasy(Okrsok* okrsok, int pocetHlasov)
{
	if (maxPocetHlasovOkrsok_ < pocetHlasov) {
		okrsok_ = okrsok;
		maxPocetHlasovOkrsok_ = pocetHlasov;
	}
	prefHlasyPocet_ += pocetHlasov;

	int* hlasy;
	Okres* okres(okrsok->dajOkres());
	if (!okresHlasy_->tryFind(okres, hlasy))
	{
		hlasy = new int(0);
		okresHlasy_->insert(okres, hlasy);
	}
	*hlasy += pocetHlasov;
}

int Kandidat::dajPreferencneHlasyOkres(Okres * okres)
{
	return *(*okresHlasy_)[okres];
}

int Kandidat::dajMaxPocetHlasovOkrsok()
{
	return maxPocetHlasovOkrsok_;
}

int Kandidat::dajPreferencneHlasyPocet()
{
	return prefHlasyPocet_;
}

Okrsok * Kandidat::dajOkrsokMaxPrefHlasyPocet()
{
	return okrsok_;
}

const string& Kandidat::dajMeno()
{
	return meno_;
}
