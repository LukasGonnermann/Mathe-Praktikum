#include "CKomplex.h"
#include <math.h>

CKomplex::CKomplex()
{
	a = 0;
	b = 0;
}

CKomplex::CKomplex(double phi)
{
	a = cos(phi);
	b = sin(phi);
}

CKomplex::CKomplex(double pA, double pB)
{
	this->a = pA;
	this->b = pB;
}

CKomplex::~CKomplex()
{
}

double CKomplex::re()
{
	return this->a;
}

double CKomplex::im()
{
	return this->b;
}

double CKomplex::abs()
{
	double erg = 0;
	erg = pow(this->a, 2) + pow(this->b, 2);
	return sqrt(erg);
}

CKomplex operator+(CKomplex z1,CKomplex z2)
{
	CKomplex erg(0, 0);
	erg.a = z1.a + z2.a;
	erg.b = z1.b + z2.b;
	return erg;
}

CKomplex operator*(CKomplex z1, CKomplex z2)
{
	CKomplex erg(0, 0);
	erg.a = (z1.a * z2.a) - (z1.b * z2.b);
	erg.b = (z1.a * z2.b) + (z2.a * z1.b);
	return erg;
}

CKomplex operator*(double reelleZahl ,CKomplex z1)
{
	double test = reelleZahl * z1.re();
	double test1 = reelleZahl * z1.im();
	CKomplex erg(reelleZahl * z1.re(), reelleZahl * z1.im());
	return erg;
}