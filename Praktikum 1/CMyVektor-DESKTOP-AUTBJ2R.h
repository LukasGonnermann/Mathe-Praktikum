#pragma once
#include <vector>
class CMyVektor
{
public:
	CMyVektor();
	CMyVektor(int pXDim);
	CMyVektor(int pXDim, int pYDim);
	CMyVektor(int pXDim, int pYDim, int pZDim);
	~CMyVektor();

	int getXDim();
	int getYDim();
	int getZDim();
	void setXDim(int pVal);
	void setYDim(int pVal);
	void setZDim(int pVal);

private:
	unsigned int Dim;
	double vektor;
};



