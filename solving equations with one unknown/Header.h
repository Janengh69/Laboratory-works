#pragma once
#include <iostream>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <vector>
#define a -5
#define b 5

using namespace std;

typedef struct {
	double a1;
	double b1;
}range;

 struct tab {
	double xn;
	double eps;
	int iter;
};
double resFunc(double x);
double derative1(double x);
double derative2(double x);

range* rangeSelection(int * length);

double iterationMethod(double a1, double b1, double eps, double* error,int maxit, bool& done, vector <tab> &iterNumber1);
double tangentMethod( double a1, double b1, double eps, double* error, int maxit, bool& done, vector <tab> &iterNumber2);
void tableIter(range* temp, int* length, vector<tab> &iterNumb1);
void tableTangent(range * temp, int* length, vector<tab>& iterNumb2);
void tableCompare(vector<tab>& iterNumber1, vector<tab>& iterNumber2);
tab make(double xn, double eps, int iter);