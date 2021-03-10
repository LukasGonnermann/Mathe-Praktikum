#include "vektor.h"
#include "matrix.h"
#include <cmath>
using namespace std;
CMyVektor mx(CMyVektor v);
CMyVektor fx(CMyVektor v);
CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
void newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

int main(void) {
	CMyVektor xJ(4);
	xJ.set_val(1,0);
	xJ.set_val(2, 1);
	xJ.set_val(0, 2);
	xJ.set_val(3, 3);
	CMyMatrix jak = jacobi(xJ,mx);

	jak.to_string();

	CMyVektor x(2);
	x.set_val(1, 0);
	x.set_val(1, 1);

	newton(x, fx);
	system("pause");
	return 0;
}

CMyVektor mx(CMyVektor v) {
	CMyVektor erg(3);
	double x1 = v.get_val(0);
	double x2 = v.get_val(1);
	double x3 = v.get_val(2);
	double x4 = v.get_val(3);

	erg.set_val(x1 * x2 * exp(x3), 0);
	erg.set_val(x2 * x3 * x4, 1);
	erg.set_val(x4, 2);

	return erg;
}


CMyVektor fx(CMyVektor v) {
	CMyVektor erg(2);
	double x = v.get_val(0);
	double y = v.get_val(1);

	erg.set_val(pow(x, 3) * pow(y, 3) - 2 * y, 0);
	erg.set_val(x - 2, 1);

	return erg;
}

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	int m = funktion(x).get_dim();
	int n = x.get_dim();

	CMyMatrix jacobi(m, n);
	double h = 0.0001;

	for (int k = 0; k < m; k++)
	{
		double fnkt = funktion(x).get_val(k);
		for (int i = 0; i < n; i++)
		{
			x.set_val(x.get_val(i) + h, i);
			jacobi.set_val((funktion(x).get_val(k) - fnkt) / h, k, i);
			x.set_val(x.get_val(i) - h, i);
		}
	}
	return jacobi;
}

void newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x)) {
	if (x.get_dim() != 2) {
		cout << "\n\n Vektor hat falsche Dimensionen! \n\n\n";
		return;
	}
	CMyVektor dx(2);
	int step = 0;

	do {
		if (funktion(x).get_length() < pow(10, -5)) {
			cout << "Ende, da ||f(x)|| < 1e-5 bei\n";

			cout << "\tx \t =\t";
			x.to_string();

			cout << "\n\tf(x) \t =\t";
			funktion(x).to_string();

			cout << "\n\t||f(x)|| =\t "
				<< funktion(x).get_length() << endl << endl;

			return;
		}

		cout << "Schritt " << step << ":\n";
		cout << "\tx \t =\t";
		x.to_string();

		cout << "\n\tf(x) \t =\t";
		funktion(x).to_string();

		cout << "\n\tf'(x) \t =\t";
		jacobi(x, funktion).get_row(0).to_string();
		cout << "\t\t\t";
		jacobi(x, funktion).get_row(1).to_string();

		cout << "\n\tf'(x)^-1 =\t";
		jacobi(x, funktion).invers().get_row(0).to_string();
		cout << "\t\t\t";
		jacobi(x, funktion).invers().get_row(1).to_string();

		cout << "\n\tdx \t =\t";
		dx = jacobi(x, funktion).invers() *  (funktion(x) * -1);
		dx.to_string();

		cout << "\n\t||f(x)|| =\t "
			<< funktion(x).get_length() << "\n\n\n\n";

		x = x + dx;
		step++;
	} while (step <= 50);
}