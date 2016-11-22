#ifndef BENCH_H
#define BENCH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::vector;



double rosenbrock(const vector<double> &individu, int d);
double somme_rosenbrock(const vector<double> &individu);
double himmelblau(const vector<double> &individu, int d);
double somme_himmelblau(const vector<double> &individu);
double somme_rastrigin(const vector<double> &individu);
double somme_sphere(const vector<double> &individu);
double ackley(const vector<double> &individu, int d);
double somme_ackley(const vector<double> &individu);
double somme_michalewicz(const vector<double> &individu);


double proba_alea();
double aleatoire(double a, double b);
void pivotement(vector<double> &Delta, int dim);

#endif 
