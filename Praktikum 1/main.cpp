#include <iostream>
#include "CMyVektor.h"
#include <vector>
using namespace std;

double funktion(CMyVektor x);
double gx(CMyVektor x);
double fx(CMyVektor x);
CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x));
void gradverf(CMyVektor x, double lambda, double(*funktion)(CMyVektor x));

int main(void) {
	double(*fktptr)(CMyVektor x) = funktion;

	cout << "f(x): " << endl << endl;
	CMyVektor vek(2);
	vek.setVal(0, 0.2);
	vek.setVal(1,-2.1);

	gradverf(vek, 1, fx);

	cout << endl << "g(x): " << endl<< endl;
	CMyVektor vek2(3);
	
	gradverf(vek2,0.1,gx);

	system("pause");
	return 0;
}

double funktion(CMyVektor x) {
	double	 erg = 0.0;
	double	 xpos = x.getVal(0), 
			 ypos = x.getVal(1);

	erg = (-1 * xpos) * (ypos * ypos);
	return erg;
}

double gx(CMyVektor x) {
	double erg = 0.0;
	double xPos = x.getVal(0), yPos = x.getVal(1), zPos = x.getVal(2);
	erg = -((2*(xPos * xPos)) - (2*xPos*yPos) + (yPos * yPos) + (zPos * zPos) - 2*xPos - 4*zPos);
	return erg;
}

double fx(CMyVektor x) {
	double erg = 0.0;
	double xpos = x.getVal(0), ypos = x.getVal(1);
	erg = sin(xpos * ypos) + sin(xpos) + cos(ypos);
	return erg;
}

CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x)) {
	CMyVektor erg(x.getDim());
	CMyVektor tmp;
	// h = 10^(-8) vorgegeben
	double h = 0.00000001;

	for (int i = 0; i < erg.getDim(); i++) {
		double value = 0.0;

		tmp = x;
		tmp.setVal(i, (tmp.getVal(i) + h));

		value = (funktion(tmp) - funktion(x)) / h;
		erg.setVal(i, value);

	}
	return erg;
}

void gradverf(CMyVektor x, double lambda, double(*funktion)(CMyVektor x)) {

	for (int steps = 1; steps <= 25; steps++) {

		if (gradient(x, funktion).getLength() < 0.00001) {
			cout << "\n\n\t!!!Verfahren beendet, da ||grad f(x)|| bei " << gradient(x, funktion).getLength() << " < 0.00001!!!\n\n";
			break;
		}
		if (steps == 25) {
			cout << "\n\n!!!Verfahren beendet, da Schritt 25 erreicht wurde!!!\n\n";
			break;
		}

		cout << "\nSchritt " << steps << ": \n\tx = ";
		x.toString();
		cout << "\tlambda = " << lambda << endl;
		cout << "\tf(x) = " << funktion(x) << endl;
		cout << "\tgrad f(x) = ";
		gradient(x, funktion).toString();
		cout << "\t||grad f(x)|| = " << gradient(x, funktion).getLength() << endl;

		CMyVektor xneu = lambda * gradient(x, funktion) + x;
		cout << "\n\txneu = ";
		xneu.toString();
		cout << "\tf(xneu) = " << funktion(xneu) << endl;

		if (funktion(xneu) > funktion(x)) {

			CMyVektor xtest = (2 * lambda) * gradient(x, funktion) + x;

			if (funktion(xtest) > funktion(xneu)) {
				x = xtest;
				lambda *= 2;
				cout << "\n\tSchrittweite wurde verdoppelt, nun bei: " << lambda << endl;

			}
			else {
				x = xneu;
				cout << "\n\tSchrittweite wurde beibehalten, aktuell bei: " << lambda << endl;
			}
			cout << "\n\txtest = ";
			xtest.toString();
			cout << "\tf(xtest) = " << funktion(xtest) << endl;
		}
		else {
			while (funktion(xneu) <= funktion(x)) {
				lambda /= 2;
				xneu = lambda * gradient(x, funktion) + x;
				cout << "\n\tSchrittweite wurde halbiert, nun bei: " << lambda << endl;
			}
			x = xneu;
		}
	}
}