#include "header.h"

int main()
{
	double initial_matrix[N][M] = { {3,  7, 6, 0,  63},
									{13,  49, 20,  15, 353},
									{20, 19,  50, 10, 437},
									{17, 7, 17, 17,  225} };
	double modified_matrix[N][M] = { {61, 1, -2, 17, 181},
									{13, 49, 20, 15, 353},
									{20, 19, 50, 10, 437},
									{31, 2, 1, 41, 238} };
	double Gequation_root[N] = { 0, 0, 0, 0 };
	double Sequation_root[N] = { 0, 0, 0, 0 };
	double error = 0, eps = 0.001;
	cout << "Gauss method:" << endl;
	print_matrix(*initial_matrix);
	if (gauss(initial_matrix, Gequation_root)) {
		cout << "SLAR was solved!\n\nRoots are ";
		for (auto i = 0; i < N; i++)
			cout << Gequation_root[i] << " ";
	}
	else {
		cout << "Error\n\n" << endl;
	}
	cout << "\n\nIteration Seidel method:" << endl;
	print_matrix(*modified_matrix);
	if (seidelMethod(modified_matrix, Sequation_root, error, eps)) {
		cout << "\nSLAR was solved!\n\nRoots are ";
		for (auto i = 0; i < N; i++)
			cout << Sequation_root[i] << " ";
		cout << "\nInfelicity in calculations: " << error << endl;
	}
	else {
		cout << "Error" << endl;
	}
	return 0;
}
