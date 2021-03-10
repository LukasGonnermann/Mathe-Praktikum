#include<iostream>
#include<vector>
#include<cmath>
#include "vektor.h"
#pragma once

using namespace std;

class CMyMatrix{
    private:
        vector<CMyVektor> m;
        int width;
        int height;

    public:
		int get_width() { return this->width; };
		int get_height() { return this->height; };
		CMyMatrix(int high, int wide) {this->create_matrix(high, wide);};
        void create_matrix(int high, int wide);        
        void to_string();
        CMyVektor get_row(int height){return m.at(height);};
        void set_row(CMyVektor vek, int height){m.at(height) = vek;};
        double get_val(int height, int width);
        void set_val(double value, int height, int width);
        void set_example();
        CMyMatrix invers();
};

CMyMatrix operator * (double skalar, CMyMatrix m) {
	for (int y = 0; y < m.get_height(); y++) {
		for (int x = 0; x < m.get_width(); x++) {

			double new_val = m.get_val(y, x) * skalar;
			m.set_val(new_val, y, x);
		}
	}
	return m;
}


CMyMatrix operator * (CMyMatrix m, double skalar) {
	return skalar * m;
}


CMyVektor operator * (CMyMatrix m, CMyVektor v) {
	CMyVektor erg(m.get_height());

	if (m.get_width() == v.get_dim()) {

		for (int y = 0; y < m.get_height(); y++) {
			double val = 0;

			for (int x = 0; x < m.get_width(); x++) {
				val += m.get_val(y, x) * v.get_val(x);
			}

			erg.set_val(val, y);
		}

	}
	else {
		cout << "\n\n!!!Matrix und Vektor sind Inkompatibel!!!\n\n\n";
	}
	return erg;
}

void CMyMatrix::create_matrix(int high, int wide) {

	for (int i = 0; i < high; i++) {
		CMyVektor v(wide);
		m.push_back(v);
	}
	this->width = wide;
	this->height = high;
}


void CMyMatrix::to_string() {

	cout << endl;
	for (int i = 0; i < height; i++) {
		cout << "\t\t\t";
		m.at(i).to_string();
	}
	cout << endl;
}


double CMyMatrix::get_val(int height, int width) {

	return m.at(height).get_val(width);
}


void CMyMatrix::set_val(double value, int height, int width) {

	m.at(height).set_val(value, width);
}

void CMyMatrix::set_example() {
	int i = 0;
	for (int y = 0; y < this->get_height(); y++) {
		for (int x = 0; x < this->get_width(); x++) {
			this->set_val(i++, y, x);
		}
	}
}

CMyMatrix CMyMatrix::invers() {
	CMyMatrix m_inv(2, 2);

	if (this->get_height() == 2 && this->get_width() == 2) {

		double inv = 1 / ((this->get_val(0, 0) * this->get_val(1, 1)) - (this->get_val(0, 1) * this->get_val(1, 0)));
		m_inv.set_val(this->get_val(1, 1), 0, 0);
		m_inv.set_val(this->get_val(0, 0), 1, 1);
		m_inv.set_val(this->get_val(0, 1) * -1, 0, 1);
		m_inv.set_val(this->get_val(1, 0) * -1, 1, 0);
		m_inv = m_inv * inv;
	}
	else {
		cerr << "\n\n!!!Keine 2x2 Matrix!!!\n\n\n";
		exit(0);
	}
	return m_inv;
}