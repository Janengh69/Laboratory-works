#include "header.h"
double func(double x) {
	return sqrt(2 * x + 1) / 2;
	
}

double funcAntiderivative(double x) {
	return (2 * x + 1) / 6 * sqrt(2 * x + 1);
}

double methodTrapezoid(int n) {
	if (n < 1)
		return 0;
	double result = func(a) / 2;
	double h1 = (b - a) / (double) n;
	for (int i = 1; i < n; i++) {
		result += func(a + h1 * i);
	}
	result += func(b) / 2;
	return result * h1;
}

double firstTable(double NewtonLeibniz) {
	double eps = 0.01;
	//double h = sqrt(12 * eps / (b - a));
	int n = (b - a) / h;
	double integralUsingTrapezoid = methodTrapezoid(n);
	double delta = fabs(NewtonLeibniz - integralUsingTrapezoid);
	cout << " --------------------------------------------------" << endl;
	cout << "| eps   |      h      |    I      |     delta     |" << endl;
	cout << " --------------------------------------------------" << endl;
	cout << "|" << eps << setw(3) << "  |   " << h << setw(7) <<" |" << integralUsingTrapezoid << "|" << delta << setw(2) << "|" << endl;
	cout << " --------------------------------------------------" << endl;

	return delta;
}

void secondTable(double delta, double NewtonLeibniz) {
	//using method of multiply recalculation
	int n = 1 / sqrt(delta);
	double integralUsingTrapezoid1 = methodTrapezoid(n);
	n *= 2;
	double integralUsingTrapezoid2 = methodTrapezoid(n);
	cout << " ------------------------------------------" << endl;
	cout << "|     delta    |       h       |    Rh    |" << endl;
	//since in the generalized trapezoidal formula the order p is 2, then here we divide by 3
	do{
		integralUsingTrapezoid1 = integralUsingTrapezoid2;
		n *= 2;
		integralUsingTrapezoid2 = methodTrapezoid(n);
		cout << " ------------------------------------------" << endl;
		cout << "|" << setprecision(9) << delta << "|" << setprecision(12) << (b - a) / (double)n << "|" << setprecision(5) << fabs(NewtonLeibniz - integralUsingTrapezoid2) << "|" << endl;
	}while (fabs(integralUsingTrapezoid2 - integralUsingTrapezoid1) / 3 > delta);

	
	cout << " ------------------------------------------" << endl;

}
