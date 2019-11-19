#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#define N 4
#define M 5
#define maxIteration 200
using namespace std;

void print_matrix(double* matrix);
bool gauss(double(*slar)[M], double* ans);

void substr(double(*slar)[M], int from, int what);
bool simplifyRow(double(*slar)[M], int row);
bool seidelMethod(double(*slar)[M], double* answer, double& error, double& eps);