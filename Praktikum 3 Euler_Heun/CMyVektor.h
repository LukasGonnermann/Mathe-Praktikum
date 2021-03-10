#pragma once
#include <iostream>
#include <vector>
#include <cmath>
class CMyVektor
{
public:
	// Dimensionen als int
	CMyVektor();
	CMyVektor(int pDimension);
	~CMyVektor();
	int getDim();
	double getVal(int pPos);
	double getLength();

	// Position(int), double(Value)
	void setVal(int pPos, double pValue);
	void createVector(int pDimension);
	void toString();

private:
	int Dimension;
	std::vector<double> vektor;
};

inline
CMyVektor operator+(CMyVektor a, CMyVektor b) {

	if (a.getDim() != b.getDim()) {
		std::cout << "Die Vektoren haben ungleiche Dimensionen!!!\n";
		return a;
	}
	else {
		for (int i = 0; i < a.getDim(); i++) {
			double setter = a.getVal(i) + b.getVal(i);
			a.setVal(i, setter);
		}
		return a;
	}
}

inline
CMyVektor operator*(double lambda, CMyVektor a) {
	for (int i = 0; i < a.getDim(); i++) {
		double setter = a.getVal(i) * lambda;
		a.setVal(i, setter);
	}
	return a;
}