#include "Header.h"

double resFunc(double x) {
	return 0.3 * exp(x) - x * x + 1;
}

double derative1(double x) {
	return 0.3 * exp(x) - 2 * x;
}

double derative2(double x) {
	return 0.3 * exp(x) - 2;
}

range* rangeSelection(int *length) {
	range* temp = (range*)malloc(sizeof(range));
	*length = 0;
	for(double step = a; step <= b-0.01; step += 0.01) {
		if ((resFunc(step) * resFunc(step + 0.01) < 0) && (derative1(step)*derative1(step+0.01) > 0)){
			*length += 1;
			temp = (range*)realloc(temp, (*length) * sizeof(range));
			temp[(*length) - 1].a1 = step;
				temp[(*length) - 1].b1 = step + 0.01;
		}
	}
	return temp;
}

double iterationMethod(double a1, double b1, double eps, double* error, int maxit, bool& done, vector<tab> &iterNumb1) {
	double M1, m1, lambda, q, xn;
	double x0 = (a1 + b1) / 2;
	done = true;
	if (fabs(derative1(a1)) > fabs(derative1(b1))) {
		M1 = derative1(a1);
		m1 = derative1(b1);
	}
	else {	
		M1 = derative1(b1);
		m1 = derative1(a1);
	}
	lambda = 1 / M1;
	q = 1 - fabs(m1 / M1);
	xn = x0;
	int count = 0;
	do {
		x0 = xn;
		xn = x0 - lambda * resFunc(x0);
		count++;
		if (count > maxit) {
			done = false;
			break;
		}
	} while (fabs(xn - x0) > (1 - q) / q * eps);
	*error = (fabs(xn - x0)) * q / (1 - q);
	if (done) {
		iterNumb1.push_back(make(xn, eps, count));
	}
	return xn;
}
tab make(double xn, double eps, int iter) {
	tab temp;
	temp.xn = xn;
	temp.eps = eps;
	temp.iter = iter;
	return temp;
}

double tangentMethod(double a1, double b1, double eps, double* error, int maxit, bool& done, vector<tab> &iterNumb2) {
	double m1, x0, xn;

	m1 = fabs(derative1(a1));

	for (double i = a1; i < b1; i += 0.001)
		if (fabs(derative1(i) < m1))  m1 = fabs(derative1(i));

	(resFunc(a1) * derative2(a1) > 0)? x0 = a1 : x0 = b1;
	xn = x0;
	int count = 0;
	do {
		xn = xn - resFunc(xn) / derative1(xn);
		count++;
		if (count > maxit) {
			done = false;
			break;
		}
	} while (fabs(resFunc(xn) / m1) > eps);
	*error = fabs(resFunc(xn)) / m1;
	if (done) {
		iterNumb2.push_back(make(xn, eps, count));
	}
	return xn;		
}
void tableIter(range* t, int *length,  vector<tab> &iterNumber1) {
	double error = 0, xn;
	bool done = true;
	cout << "\tIteration method:\n";
	cout << "-------------------------------------------" << endl;
	cout << "|  Eps  |       Xn      |      Error      |" << endl;
	cout << "-------------------------------------------" << endl;
	for (int i = 0; i < (*length); i++) {
		for (double eps = 1e-2; eps >= 1e-14; eps *= 1e-3) {
			xn = iterationMethod(t[i].a1, t[i].b1,  eps, &error, 150, done,  iterNumber1);
			if (done) {
				cout << "|" << setw(7) << eps << "|" << setprecision(11) << setw(15) << xn << "|" << setprecision(11) << setw(17) << error << "|" << endl;
			}
			else {
				cout << "|" << setw(7) << eps << "|" << setprecision(11) << setw(16)  << " not found   |" << setprecision(11) << setw(18) << " not found    |" << endl;
			}
		}
		cout << "-------------------------------------------" << endl;
	}
	cout << endl;
}

void tableTangent(range* t, int* length, vector<tab> &iterNumb2) {
	double error = 0, xn;
	bool done = true;
	cout << "\tTangent method:\n";
	cout << "-------------------------------------------" << endl;
	cout << "|  Eps  |      Xn       |     Error       |" << endl;
	cout << "-------------------------------------------" << endl;

	for (int i = 0; i < (*length); i++) {
		for (double eps = 1e-2; eps >= 1e-14; eps *= 1e-3) {
			xn = tangentMethod(t[i].a1, t[i].b1, eps, &error, 150, done, iterNumb2);
			if (done) {
				cout << "|" << setw(7) << eps << "|" << setprecision(11) << setw(15) << xn << "|" << setprecision(11) << setw(17) << error << "|" << endl;
			}
			else {
				cout << "|" << setw(7) << eps << "|" << setprecision(11) << setw(16) << " not found   |" << setprecision(11) << setw(18) << " not found    |" << endl;
			}
		}
		cout << "-------------------------------------------" << endl;
	}
	cout << endl;
}
void tableCompare(vector<tab>& iterNumber1, vector<tab>& iterNumber2) {
	cout << "\tNumber of iterations:\n";
	cout << "-------------------------------------------------------" << endl;
	cout << "|    Xn       |  Eps  |Iteration method|Tangent method|" << endl;
	cout << "-------------------------------------------------------" << endl;
	int temp;
	(iterNumber1.size() < iterNumber2.size()) ? temp = iterNumber1.size() : temp = iterNumber2.size();
	for (auto i = 0; i < temp; i++) 
		cout << "|" << setw(13) << iterNumber1[i].xn << "| " << setw(6) << iterNumber1[i].eps << "|  "  << setw(6) << iterNumber1[i].iter << setw(12) << "|   " << setw(6) <<  iterNumber2[i].iter << setw(6) <<  "|" << endl;
	cout << "------------------------------------------------------" << endl;

}