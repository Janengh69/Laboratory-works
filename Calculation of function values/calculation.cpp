	#include "header.h"

	double Rn_calc(double eps, int& n, double& x, double& result) {
		double Un = 1, int_x = 1, float_x = 1, Rn = 1, divx = 0, modx = 0;

		divx = modf(x, &modx);   // [x] + {x}
		int_x = exp(double(modx));// e^[x]

		while (abs(Un) >= eps) { //while Un >= epsilon
			Un = divx * Un / n; // Uk = [x] * Uk-1 / k
			float_x = float_x + Un; // Sk = Sk-1 + Uk
			n++;	//k++
		}
		//Sk == e^{x}
		result = float_x * int_x;		//e^x = e^[x]*e^{x}

		for (int i = 0; i <= n; i++) {
			Rn = Rn * abs(divx) / (i + 1);	// R = |x|^n+1 /(n+1)!
		}
		Rn = Rn * (n + 1) / n; // R = R * n+1 / n

		return Rn;
	}
