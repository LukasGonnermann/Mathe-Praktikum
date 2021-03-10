#include"CLotto.h"
bool enthaelt(std::vector<int> vec, int comp) {
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == comp) return true;
	}
	return false;
}

CLotto::CLotto(int n)
{
	if (n <= 0)	random.initialisiere(time(NULL));
	else random.initialisiere(n);
}

CLotto::~CLotto()
{
}

void CLotto::setTippzettel(std::vector<int> vec)
{
	Tippzettel = vec;
}

int CLotto::lottoZiehung()
{
	int res = 0;
	std::vector<int> ziehung;
	// Init mit 0
	for (int  i = 0; i < 6; i++)
	{
		ziehung.push_back(0);
	}
	ziehung = lottoSim();
	for (int i = 0; i < 6; i++)
	{
		if (enthaelt(ziehung,Tippzettel.at(i)))
		{
			res++;
		}
	}
	return res;
}

int CLotto::lottoDoppelZiehung()
{
	int res = 0;
	std::vector<int> ziehung1;
	std::vector<int> ziehung2;
	// Init mit 0
	for (int i = 0; i < 6; i++)
	{
		ziehung1.push_back(0);
		ziehung2.push_back(0);
	}
	ziehung1 = lottoSim();
	ziehung2 = lottoSim();
	for (int i = 0; i < 6; i++)
	{
		if (enthaelt(ziehung1, ziehung2.at(i)))
		{
			res++;
		}
	}
	return res;
}

std::vector<int> CLotto::lottoSim()
{
	int i = 0, tmp;
	std::vector<int> res;
	// Mit 0 Init
	for (int i = 0; i < 6; i++)
	{
		res.push_back(0);
	}
	while (i < 6)
	{
		tmp = random.wert(1, 49);
		if (!enthaelt(res,tmp))
		{
			res.at(i) = tmp;
			i++;
		}
	}
	return res;
}