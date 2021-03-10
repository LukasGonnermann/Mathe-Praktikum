#include <iostream>
#include "CMyVektor.h"
#include "C_DGLSolver.h"

CMyVektor fkt1(CMyVektor y, double x);
double fkt2(CMyVektor y, double x);
double fkt3(CMyVektor y, double x);

int main(void) {
	/*
	C_DGLSolver fk1Solver(&fkt1);
	CMyVektor y1 = CMyVektor(2);
	y1.setVal(0, 0);
	y1.setVal(1, 1);
	fk1Solver.eulerVerfahren(0,y1,2,100,0);
	std::cout << "---------------------------------------------------------" << std::endl;
	fk1Solver.heunVerfahren(0, y1, 2, 100, 0);

	C_DGLSolver fk2Solver(&fkt2);
	CMyVektor y = CMyVektor(3);
	y.setVal(0,1);
	y.setVal(1,-1);
	y.setVal(2,2);
	fk2Solver.eulerVerfahren(1,y,2,10,0.5);
	std::cout << "---------------------------------------------------------" << std::endl;
	fk2Solver.heunVerfahren(1, y, 2, 10, 0.5);
	*/
	

	C_DGLSolver fk3Solver(&fkt3);
	CMyVektor y3 = CMyVektor(3);
	y3.setVal(0,-2.0);
	y3.setVal(1, 1.0);
	y3.setVal(2, 12.0);
	fk3Solver.heunVerfahren(1.0,y3,2.0,100,0.0);


	system("pause");
	return 0;
}

CMyVektor fkt1(CMyVektor y, double x) {
	CMyVektor res = CMyVektor(2);
	double tmp = 2 * y.getVal(1) - x * y.getVal(0);
	res.setVal(0, tmp);
	tmp = y.getVal(0) * y.getVal(1) - 2 * pow(x, 3);
	res.setVal(1, tmp);
	return res;
}

double fkt2(CMyVektor y,double x) {
	return 2 * x*y.getVal(1)*y.getVal(2) + 2 * y.getVal(0)*y.getVal(0)*y.getVal(1);
}

double fkt3(CMyVektor y, double x) {
	return ((2 * y.getVal(1) * y.getVal(2) / (9 * x)) - ((32 / 3) * y.getVal(0)));
}