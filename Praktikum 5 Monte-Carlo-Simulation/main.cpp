#include "CZufall.h"
#include "CLotto.h"
#include <iostream>
using namespace std;

void print(std::vector<int> vec);
void monteCarlo(int N, int k, bool einzelZiehung, CLotto lotto);

void testCZufall();

int main() {
	cout << "Press Enter to Start with CZufall Test: " << endl;
	cin.get();
	cout << endl << "------------------------------------------------------------" << endl;
	testCZufall();
	cout << endl << "------------------------------------------------------------" << endl;
	cout << "Press Enter to Start with Monte-Carlo simulation: ";
	cin.get();
	cout << "------------------------------------------------------------" << endl;
	cout << "Runde 1... (Doppelziehung)" << endl;
	CLotto myLotto(0);
	monteCarlo(100000,3,false,myLotto);
	cout << endl << "Runde 2... (Tippzettel)" << endl;
	CLotto myLotto2(0);
	vector<int> Tippzettel = { 1,2,3,4,5,6 };
	myLotto2.setTippzettel(Tippzettel);
	monteCarlo(100000, 3, true, myLotto2);
	cout << endl << "------------------------------------------------------------" << endl;
	cin.get();
}

void print(std::vector<int> vec) {
	std::cout << "(";
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i];
		if (i < vec.size() - 1) std::cout << "|";
	}
	std::cout << ")" << std::endl << std::endl;
}

void testCZufall() {
	CZufall rdm;
	vector<int> tmp;
	int n = 10;
	for (int i = 0; i < 20; i++)
	{
		cout << "i: " << i << " | const n = 10" << endl;
		rdm.initialisiere(n);
		tmp = rdm.test(3,7,10000);
		print(tmp);
	}
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		n = rand() % 100;
		cout << "i: " << i << " | Verschiedene Werte fuer n = "<< n <<endl;
		rdm.initialisiere(n);
		tmp = rdm.test(3,7,10000);
		print(tmp);
	}
	cout << endl;
	for (int i = 0; i < 20; i++)
	{
		n = time(NULL);
		cout << "i: " << i << " n abhaengig von der Zeit: n = " << n << endl;
		rdm.test(3,7,10000);
		print(tmp);
	}
	cout << "Falscher Test:" << endl;
	print(rdm.test_falsch(3, 7, 10000));
}

void monteCarlo(int N, int k, bool einzelZiehung, CLotto lotto) {
	double res = 0;
	int tmp = 0;
	if (einzelZiehung)
	{
		for (int i = 0; i < N; i++)
		{
			tmp = lotto.lottoZiehung();
			if (tmp == k)
			{
				res++;
			}
		}
		res = res / N;
		res = res * 100;
		cout << "Die Wahrscheinlichkeit, dass bei " <<  N << " Ziehungen genau " << k << " Zahlen Uebereinstimmen ist " << res << "%" << endl;
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			tmp = lotto.lottoDoppelZiehung();
			if (tmp == k)
			{
				res++;
			}
		}
		res = res / N;
		res = res * 100;
		cout << "Die Wahrscheinlichkeit, dass bei " << N << " Ziehungen genau " << k << " Zahlen Uebereinstimmen ist " << res << "%" << endl;
	}
}