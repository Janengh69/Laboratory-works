	#include "header.h"
	int main() {
		double eps = 0.01, Rn = 0, abserr = 0, res = 0;
		int n = 1;
		double x = -6.2;//(a + b) / 2;;
		double h = (b - a) / 10;
		cout << "|------------------------------------------------------------------------\n";
		cout << setw(40) << "TABLE1" << setw(33) << "|" << endl;
		cout << "|-----------------------------------------------------------------------|\n";
		cout << "|   Epsilon    |  n  | Absolute Error  |       Rn        |     Result   |\n";
		for (int i = 0; i <= table_len; i++) {
			Rn = Rn_calc(eps, n, x, res);
			abserr = abs(res - exp(x));
			cout << "|-----------------------------------------------------------------------|\n";

			printf("|%13e | %3d | %15e | %15e | %13f|\n", eps, n, abserr, Rn, res);
			n = 1;
			res = 0;
			eps = eps / 1000;
			

		}
		cout << "-------------------------------------------------------------------------\n";

		cout << "\n\n ---------------------------------------------------------\n";
		cout << "|" <<  setw(45) << "TABLE2 (eps = 1.0e-008)"  << setw(12) << "|" << endl;
		cout << "|--------------------------------------------------------|\n";
		cout << "|  x   |  Absolute Error |     Rn        |     Result    |" << endl;
		eps = 0.00000001;
	
		for (int i = 0; i <= 10; i++) {
			x = a + h * i;
			Rn = Rn_calc(eps, n, x, res);
			abserr = abs(res - exp(x));
			cout << "|--------------------------------------------------------|\n";
			printf("|%6.2f %15e %16e %16f|\n", x, abserr, Rn, res);
			n = 1;
			res = 0;

		}
		cout << "---------------------------------------------------------\n";

		return 0;
	}

