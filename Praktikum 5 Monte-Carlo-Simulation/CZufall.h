#pragma once
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>

class CZufall
{
public:
	// Gibt Zufallszahl zwischen a und b
	int wert(int a, int b);
	void initialisiere(int n);
	std::vector<int> test(int a, int b, int N);
	std::vector<int> test_falsch(int a, int b, int N);
};