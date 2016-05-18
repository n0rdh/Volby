#pragma once

#include <vector>
#include <string>
#include <fstream>


class Parser
{
public:
	static const int POCET_POL_STRAN = 23;

	Parser(const std::string& nazovSuboru);
	Parser(const Parser& dalsi);
	~Parser();

	static const std::string prelozCestu(const std::string& cesta);

	Parser& operator=(const Parser& dalsi);

	const std::string& dajNazovStrany(const int cisloStrany) const;

	const std::string& dajStrDataNaPozicii(int index) const;
	int dajIntDataNaPozicii(int index) const;

	bool nacitajDalsiZaznam(char oddelovac);

private:
	static int prevedStrNaInt(const std::string& token);
	void nacitajSuborPoRiadkoch(const std::string& nazovSuboru, std::vector<std::string>* zoznam);
	std::vector<std::string>* rozdelRiadokNaCasti(const std::string& retazec, char oddelovac) const;

	std::vector<std::string>* prvkyRiadku_;
	std::fstream subor_;
	std::vector<std::string>* strany_;
};