#pragma once
#include "CZufall.h"

class CLotto
{
public:
	CLotto(int n);
	~CLotto();
	void setTippzettel(std::vector<int> vec);
	int lottoZiehung();
	int lottoDoppelZiehung();

private:
	CZufall random;
	std::vector<int> Tippzettel;
	std::vector<int> lottoSim();
};

