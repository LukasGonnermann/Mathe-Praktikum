#pragma once
#include <vector>
class CKomplex
{
private:
	double a, b;

public:
	CKomplex();
	CKomplex(double phi);
	CKomplex(double pA, double pB);
	~CKomplex();

	double re();
	double im();
	double abs();

	friend CKomplex operator+(CKomplex z1, CKomplex z2);
	friend CKomplex operator*(CKomplex z1, CKomplex z2);
	friend CKomplex operator*(double reelleZahl, CKomplex z1);
};