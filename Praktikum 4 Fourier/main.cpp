#include <iostream>
#include <fstream>
#include "CKomplex.h"
#include <math.h>
#define PI atan(1) * 4

using namespace std;

vector<CKomplex> werte_einlesen(const char *dateiname);
void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon = -1);
void abweichung(vector<CKomplex> a, vector<CKomplex> b, double epsilon);
vector<CKomplex> transformation(vector<CKomplex> a, bool hin);


int main() {
	cout << "Einlesen..." << endl;	
	vector<CKomplex> werte = werte_einlesen("Daten_original.txt");
	cout << "Transformieren..." << endl;
	vector<CKomplex> trans_werte = transformation(werte,1);
	cout << "Ausgeben..." << endl;
	werte_ausgeben("eDefault.txt",trans_werte);
	werte_ausgeben("e1.txt", trans_werte,0.1);
	werte_ausgeben("e2.txt", trans_werte,1.0);
	cout << "Ruecktrans..." << endl;
	vector<CKomplex> werteEDefault = werte_einlesen("eDefault.txt");
	vector<CKomplex> rueckEDefault = transformation(werteEDefault, 0);
	vector<CKomplex> werteE1 = werte_einlesen("e1.txt");
	vector<CKomplex> rueckE1 = transformation(werteE1, 0);
	vector<CKomplex> werteE2 = werte_einlesen("e2.txt");
	vector<CKomplex> rueckE2 = transformation(werteE2, 0);

	abweichung(werte,rueckEDefault,-1);
	abweichung(werte,rueckE1,0.1);
	abweichung(werte,rueckE2,1.0);
	
	system("pause");
	return 0;
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

vector<CKomplex> transformation(vector<CKomplex> value, bool hin)
{
	int N = value.size();
	vector<CKomplex> res;
	int j = 0;
	if (hin)
	{
		j = -1;
	}
	else
	{
		j = 1;
	}
	for (int n = 0;n < N; n++)
	{
		CKomplex sum(0,0);
		for (int k = 0;k < N;k++)
		{
			sum = sum + value.at(k) * CKomplex(j * ((2 * PI * k * n)/ N));
		}
		res.push_back((1/ sqrt(N)) * sum);
	}
	return res;
}


void abweichung(std::vector<CKomplex> a, std::vector<CKomplex> b, double epsilon) {
	double max = 0, tmp = 0;
	for (int i = 0; i < a.size(); i++) 
	{
		if (b[i].re() != 0) 
		{
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