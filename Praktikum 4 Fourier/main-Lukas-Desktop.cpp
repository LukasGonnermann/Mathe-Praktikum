#include <iostream>
#include <fstream>
#include "CKomplex.h"
#include <math.h>
#define PI 3.14159265358979323846

using namespace std;

vector<CKomplex> werte_einlesen(const char *dateiname);
void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon = -1);
vector<CKomplex> transformation(vector<CKomplex> values, bool enable);
void deviation(vector<CKomplex> a, vector<CKomplex> b, double epsilon);


double rnd(double val);


int main() {
	cin.get();
	cout << "Werte einlesen: " << endl;
	vector<CKomplex> werte = werte_einlesen("Daten_original.txt");
	cout << "Werte eingelesen!" << endl << "Werte ausgeben:" << endl;
	werte_ausgeben("Alle_Daten_Ausgegeben.txt",werte,-1);
	werte_ausgeben("Daten_bis_5.txt", werte, 5);
	cin.get();
}

vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();
	
	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}

CKomplex hin(std::vector<CKomplex> values, long len, int pos) {
	double reRes = 0, imRes = 0;

	for (int i = 0; i < len; i++) {
		reRes += values[i].re()*cos((2.*pos*i*PI) / len);
	}
	reRes *= (2. / len);

	for (int i = 0; i < len; i++) {
		imRes += sin((2.*pos*i*PI) / len) * values[i].re();
	}
	imRes *= (2. / len);

	return CKomplex(reRes, imRes);
}

CKomplex hinNew(std::vector<CKomplex> values, long len, int pos) {
	CKomplex res = CKomplex();
	for (int k = 0; k <= (len - 1); k++) {
		res = res + values[k].re()*CKomplex((-2.*PI*k*pos) / len);
	}
	return (1 / sqrt(len))*res;
}


double re(std::vector<CKomplex> values, long len, int pos) {
	if (values[pos].re() == 0) {
		return 0;
	}
	double res = 0.5*values[0].re();
	if (len % 2 == 0) {
		for (int i = 1; i <= ((len / 2) - 1); i++) {
			
			res += values[i].re()*cos((2.*pos*i*PI) / len) + values[i].im()*sin((2.*pos*i*PI) / len);
		}
		res += 0.5*values[len / 2].re()*cos(PI*pos);
	}
	else {
		for (int i = 1; i <= ((len - 1) / 2); i++) {
			res += values[i].re() * cos((2.*pos*i*PI) / len) + values[i].im()*sin((2.*pos*i*PI) / len);
		}
	}
	return res;
}

double reNew(std::vector<CKomplex> values, long len, int pos) {
	double res = 0;
	for (int n = 0; n <= (len - 1); n++) {
		res = res + (values[n] * CKomplex((2.*PI*n*pos) / len)).re();
	}
	return (1 / sqrt(len))*res;
}

vector<CKomplex> transformation(std::vector<CKomplex> values, bool enable) {
	vector<CKomplex> res;
	long length = values.size();
	res.resize(length);
	CKomplex tmp = CKomplex();
	for (int i = 0; i < length; i++) {
		res[i] = tmp;
	}

	if (enable) {
		for (int i = 0; i < length; i++) {
			res[i] = hinNew(values, length, i);
		}
	}
	else {
		for (int i = 0; i < length; i++) {
			tmp = CKomplex(reNew(values, length, i), 0);
			res[i] = tmp;
		}
	}
	return res;
}

void deviation(std::vector<CKomplex> a, std::vector<CKomplex> b, double epsilon) {
	double max = 0, tmp = 0;
	for (int i = 0; i < a.size(); i++) {
		if (b[i].re() != 0) {
			tmp = a[i].re() - b[i].re();
			if (tmp < 0) {
				tmp *= -1;
			}
			if (tmp > max) {
				max = tmp;
			}
		}
	}
	std::cout << "Die maximale Abweichung bei e = " << epsilon << " liegt bei " << max << std::endl;
}

double rnd(double val) {
	const int points = 5;
	int tmp = val * pow(10, points);
	double res = (tmp) / pow(10.0, points);
	return res;
}