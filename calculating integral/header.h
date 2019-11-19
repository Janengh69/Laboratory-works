#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#define b 15
#define a 0
#define h 0.04 
using namespace std;
double func(double x);
double funcAntiderivative(double x);
double methodTrapezoid(int n);
double firstTable(double NewtonLeibniz);
void secondTable(double delta, double NewtonLeibniz);
