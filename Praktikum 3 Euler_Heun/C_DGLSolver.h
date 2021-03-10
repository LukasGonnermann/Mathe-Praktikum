#pragma once
#include "CMyVektor.h"

class C_DGLSolver
{
public:
	// TODO:
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x));
	
	void eulerVerfahren(double start, CMyVektor y ,double end, int steps, double erg);
	void heunVerfahren(double start, CMyVektor y, double end, int numSteps, double sol);
	~C_DGLSolver();

private:
	bool hoheOrdnung;
	CMyVektor(*dgl_ptr)(CMyVektor y, double x);
	double(*dgl_ptr_hoch)(CMyVektor y, double x);
	CMyVektor ableitungen(CMyVektor y, double x);
};