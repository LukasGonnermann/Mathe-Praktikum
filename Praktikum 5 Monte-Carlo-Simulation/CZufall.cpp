#include "CZufall.h"
int CZufall::wert(int a, int b)
{
	int res = b - a + 1;
	res = rand() % res;
	res += a;
	return res;
}

void CZufall::initialisiere(int n)
{
	srand(n);
}

std::vector<int> CZufall::test(int a, int b, int N)
{
	int size = b - a + 1, tmp = 0;
	std::vector<int> res;
	for (int i = 0; i < size; i++)
	{
		res.push_back(0);
	}
	for (int i = 0; i < N; i++)
	{
		tmp = wert(a,b);
		++res[tmp - a];
	}
	return res;
}

std::vector<int> CZufall::test_falsch(int a, int b, int N)
{
	int size = b - a + 1, tmp = 0;
	std::vector<int> res;
	for (int i = 0; i < size; i++)
	{
		res.push_back(0);
	}
	for (int i = 0; i < N; i++)
	{
		initialisiere(time(NULL));
		tmp = wert(a, b);
		++res[tmp - a];
	}
	return res;
}