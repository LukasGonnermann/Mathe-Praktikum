#include "CMyVektor.h"
CMyVektor::CMyVektor()
{
}

CMyVektor::CMyVektor(int pDimension)
{
	this->Dimension;
	createVector(pDimension);
}

CMyVektor::~CMyVektor()
{
}

void CMyVektor::createVector(int pDimension)
{
	for (int i = 0; i < pDimension;i++ )
	{
		vektor.push_back(0.0);
	}
}

void CMyVektor::toString()
{
	using namespace std;
	cout << "{ ";
	for (unsigned int i = 0;i < vektor.size(); i++)
	{
		cout << vektor.at(i);

		if (i == vektor.size() - 1) {
			cout << " }" << endl;
		}
		else {
			cout << " , ";
		}
		
	}
}

int CMyVektor::getDim()
{
	return vektor.size();
}

double CMyVektor::getVal(int pPos)
{
	return vektor.at(pPos);
}

void CMyVektor::setVal(int pPos, double pValue)
{
	vektor.at(pPos) = pValue;
}

double CMyVektor::getLength()
{
	double length = 0;
	for (unsigned int i = 0; i < vektor.size(); i++) {
		length += (vektor.at(i) * vektor.at(i));
	}
	length = sqrt(length);
	return length;
}

