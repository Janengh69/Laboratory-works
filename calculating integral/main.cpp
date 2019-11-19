#include "header.h"

int main() {
	//calculating integral by Newton-Leibniz formula
	double NewtonLeibniz = funcAntiderivative(b) - funcAntiderivative(a);
	cout << "\nIntegral sqrt(2x+1)/2 from 0 to 15:" << endl;
	cout << "\nI = " << setprecision(10) << NewtonLeibniz << endl << endl;
	double delta = firstTable(NewtonLeibniz);
	secondTable(delta, NewtonLeibniz);
	return 0;
}