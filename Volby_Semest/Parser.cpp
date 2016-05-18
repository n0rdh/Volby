#include <sstream>
#include <iostream>

#include "Parser.h"

using namespace std;

Parser::Parser(const string & nazovSuboru) :
	strany_(new vector<string>()),
	prvkyRiadku_(nullptr)
{
	nacitajSuborPoRiadkoch(prelozCestu("zoznamStran.txt"), strany_);
	subor_.open(prelozCestu(nazovSuboru), std::fstream::in);
}

Parser::Parser(const Parser & dalsi) :
	prvkyRiadku_(new vector<string>(*dalsi.prvkyRiadku_)),
	strany_(new vector<string>(*dalsi.strany_))
{
}

Parser::~Parser()
{
	if (subor_.is_open())
	{
		subor_.close();
	}

	delete prvkyRiadku_;
	delete strany_;
}

const string Parser::prelozCestu(const string & cesta)
{
	return string("..\\data\\") + cesta;
}

Parser & Parser::operator=(const Parser & dalsi)
{
	if (this != &dalsi)
	{
		*prvkyRiadku_ = *dalsi.prvkyRiadku_;;
		*strany_ = *dalsi.strany_;
	}

	return *this;
}

const string & Parser::dajNazovStrany(const int cisloStrany) const
{
	return strany_->at(cisloStrany);
}

const string & Parser::dajStrDataNaPozicii(int index) const
{
	return prvkyRiadku_->at(index);
}

int Parser::dajIntDataNaPozicii(int index) const
{
	return prevedStrNaInt(prvkyRiadku_->at(index));
}

bool Parser::nacitajDalsiZaznam(char oddelovac)
{
	if (subor_.eof())
	{
		return false;
	}

	string riadok;
	getline(subor_, riadok);
	delete prvkyRiadku_;
	prvkyRiadku_ = rozdelRiadokNaCasti(riadok, oddelovac);

	return true;
}

int Parser::prevedStrNaInt(const string & token)
{
	if (token.empty())
	{
		return 0;
	}

	const size_t pozicia(token.find("\""));
	const char* str(token.c_str());
	int vysledok;

	if (pozicia == string::npos)
	{
		sscanf(str, "%d", &vysledok);
	}
	else
	{
		int prvaCast, druhaCast;

		sscanf(str, "\"%d,%d\"", &prvaCast, &druhaCast);
		vysledok = (prvaCast * 1000) + druhaCast;
	}

	return vysledok;
}

void Parser::nacitajSuborPoRiadkoch(const string & nazovSuboru, vector<string>* zoznam)
{
	fstream subor(prelozCestu(nazovSuboru), std::fstream::in);

	string riadok;
	while (getline(subor, riadok))
	{
		zoznam->push_back(riadok);
	}

	subor.close();
}

vector<string>* Parser::rozdelRiadokNaCasti(const string & retazec, char oddelovac) const
{
	vector<string>* prvky(new vector<string>());
	stringstream strStream(retazec);
	string prvok;
	size_t poslednaPozOddelovaca(retazec.find_last_of(oddelovac));
	bool konciOddelovacom(false);

	if (poslednaPozOddelovaca == (retazec.size() - 1))
	{
		konciOddelovacom = true;
	}

	while (getline(strStream, prvok, oddelovac))
	{
		prvky->push_back(prvok);
	}

	if (konciOddelovacom)
	{
		prvky->push_back("");
	}

	return prvky;
}
