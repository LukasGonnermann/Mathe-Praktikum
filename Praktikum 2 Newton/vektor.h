#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#pragma once

class CMyVektor{

    private:
        std::vector<double> v;
    public:
        CMyVektor(int dims) {this->create_vec(dims);};
        void create_vec(int dims);        
        void to_string();
        int get_dim() {return v.size();};
        double get_val(int place) {return v.at(place);};
        void set_val(double value, int place) {v.at(place) = value;};
        double get_length();
};

CMyVektor operator*(double lambda, CMyVektor a) {
	for (int i = 0; i < a.get_dim(); i++) {
		double setter = a.get_val(i) * lambda;
		a.set_val(setter, i);
	}
	return a;
}


CMyVektor operator*(CMyVektor a, double lambda) {
	return lambda * a;
}

CMyVektor operator+(CMyVektor a, CMyVektor b) {

	if (a.get_dim() != b.get_dim()) {
		std::cout << "Die Vektoren haben ungleiche Dimensionen!!!\n";
		return a;
	}
	else {
		for (int i = 0; i < a.get_dim(); i++) {
			double setter = a.get_val(i) + b.get_val(i);
			a.set_val(setter, i);
		}
		return a;
	}
}

void CMyVektor::create_vec(int dims) {

	for (int i = 0; i < dims; i++) {
		v.push_back(0.0);
	}
}

void CMyVektor::to_string() {
	std::cout << "{";
	for (int i = 0; i < v.size(); i++) {
		std::cout << std::setw(10) << v[i];
		if (i == v.size() - 1) {
			std::cout << "}\n";
		}
		else {
			std::cout << ", ";
		}
	}
}

double CMyVektor::get_length() {
	double length = 0;
	for (int i = 0; i < v.size(); i++) {
		length += (v.at(i) * v.at(i));
	}
	length = sqrt(length);
	return length;
}