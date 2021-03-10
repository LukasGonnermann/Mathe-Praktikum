#include "C_DGLSolver.h"
#include <math.h>

C_DGLSolver::C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x))
{
	// Explizites Differenzialgleichungssystem 1. Ordnung:
	dgl_ptr = f_DGL_System;
	hoheOrdnung = false;
}

C_DGLSolver::C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x))
{
	// Hoehere Ordnung:
	dgl_ptr_hoch = f_DGL_nterOrdnung;
	hoheOrdnung = true;
}

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
	if (!hoheOrdnung)
	{
		return dgl_ptr(y, x);
	}
	else
	{
		int dim = y.getDim();
		CMyVektor res = CMyVektor(dim);
		// "nach oben verschieben"
		for (int i = 0; i < dim - 1; i++) {
			res.setVal(i, y.getVal(i + 1));
		}
		res.setVal(dim - 1, dgl_ptr_hoch(y, x));
		return res;
	}
}

void C_DGLSolver::eulerVerfahren(double start, CMyVektor y, double end, int steps, double sol)
{
	using namespace std;
	// h = Endwert - Startwert(Strecke) / steps;
	double h = (end - start) / steps;
	CMyVektor pre = y, akt = y;
	cout << "Schritt 0:	" << endl;
	cout << "		x =	" << start << endl;
	cout << "		y = ";
	y.toString();
	cout << endl;

	akt = ableitungen(pre, start);
	cout << "		y' = ";
	akt.toString();

	akt = pre + h * akt;
	pre = akt;

	for (int i = 1; i < steps; i++)
	{
		start += h;
		cout << "Schritt " << i << ": " << endl;
		cout << "		x =	" << start << endl;
		cout << "		y = ";
		pre.toString();

		akt = ableitungen(pre, start);
		cout << "		y' = ";
		akt.toString();

		akt = pre + h * akt;
		pre = akt;
	}

	cout << " Ende bei:" << endl;
	start += h;
	cout << "		x = " << start << endl <<
		"		y = ";
	akt.toString();
	cout << endl;

	// Abweichung:
	if (hoheOrdnung)
	{
		double dev = akt.getVal(0);
		dev -= sol;
		cout << endl << "Abweichung bei Euler bei " << steps << " Schritten: " << dev << endl;
	}
}

void C_DGLSolver::heunVerfahren(double start, CMyVektor y, double end, int steps, double sol) 
{
	using namespace std;
	double h = (end - start) / steps;
	CMyVektor akt = y, aktHelp = CMyVektor(), test = CMyVektor(), testHelp = CMyVektor(), mittel = CMyVektor();
	double x = start, x_test = x;

	cout << "Schritt 0:" << endl;
	cout << "    x = " << x << endl;
	cout << "    y = ";
	akt.toString();

	cout << "    y' = ";
	// Akt Steigung
	aktHelp = ableitungen(akt, x);
	aktHelp.toString();

	cout << std::endl;
	std::cout << "    test = ";
	// Testschritt:
	test = akt + h * aktHelp;
	test.toString();

	cout << "    test' = ";
	x_test += h;
	// Steigung vom Testschritt
	testHelp = ableitungen(test, x_test);
	testHelp.toString();

	cout << std::endl;
	cout << "    mittel = ";
	// Mittel von der beiden Steigungen
	mittel = 0.5*(aktHelp + testHelp);
	mittel.toString();

	for (int i = 1; i < steps; i++) {
		x += h;
		x_test = x;

		cout << "Schritt " << i << ":" << endl;
		cout << "    x = " << x << endl;
		cout << "    y = ";
		akt = akt + h * mittel;
		akt.toString();

		cout << "    y' = ";
		aktHelp = ableitungen(akt, x);
		aktHelp.toString();

		cout << endl;
		cout << "    test = ";
		test = akt + h * aktHelp;
		test.toString();

		cout << "    test' = ";
		x_test += h;
		testHelp = ableitungen(test, x_test);
		testHelp.toString();

		cout << endl;
		cout << "    mittel = ";
		mittel = 0.5*(aktHelp + testHelp);
		mittel.toString();
	}
	cout << "Ende bei:" << endl;
	x += h;
	cout << "    x = " << x << endl;
	cout << "    y = ";
	akt = akt + h * mittel;
	akt.toString();
	cout << endl;

	// Abweichung
	if (hoheOrdnung) {
		double dev = akt.getVal(0);
		dev -= sol;
		cout << endl << "Abweichung bei Heun bei " << steps << " Schritten: " << dev << endl << endl;
	}
}

C_DGLSolver::~C_DGLSolver()
{
}