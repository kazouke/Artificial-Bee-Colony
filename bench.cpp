#define _USE_MATH_DEFINES
#include <cmath>
#include "bench.h"

double rosenbrock(const vector<double> &individu, int d)
{
    double a=individu[d+1]-individu[d]*individu[d],
           b=1 - individu[d];
	return b*b + 100*a*a;
}

double somme_rosenbrock(const vector<double> &individu)
{
	double j=0;

	for(unsigned int i=0;i<individu.size()-1;++i)
	{
		j+=rosenbrock(individu,i);
	}

	return j;
}

double himmelblau(const vector<double> &individu, int d)
{
    double a{individu[d] * individu[d] + individu[d + 1] - 11},
           b{individu[d] + individu[d + 1] * individu[d + 1] - 7};
    return a * a + b * b;
}

double somme_himmelblau(const vector<double> &individu)
{
    double j{};
    for(unsigned int i{} ; i < individu.size() - 1 ; ++i)
        j += himmelblau(individu, i);
    return j;
}

double somme_rastrigin(const vector<double> &individu)
{
    double j{};
    for(auto x : individu)
        j += x * x - 10 * std::cos(2 * M_PI * x);
    return 10 * individu.size() + j;
}

double somme_sphere(const vector<double> &individu)
{
    double j{};
    for(auto x : individu)
        j += x * x;
    return j;
}

double somme_ackley(const vector<double> &individu)
{
    double s1{}, s2{};
    for(unsigned int i{} ; i < individu.size() ; ++i){
        double x{individu[i]};
        s1 += x * x;
        s2 += std::cos(2 * M_PI * x);
    }
    return - 20 * exp(-0.2 * sqrt(s1 / individu.size())) - exp(s2 / individu.size()) + exp(1) + 20;
}

double somme_michalewicz(const vector<double> &individu)
{
    double j{};
    for(unsigned int i{} ; i < individu.size() ; ++i){
        double x{individu[i]};
        j += std::sin(x) * std::pow(std::sin(i * x * x / M_PI), 20);
    }
    return -j;
}

double proba_alea()
{
    return 1.0*rand()/RAND_MAX;
}

double aleatoire(double a, double b)
{
    return (proba_alea()-b/(b-a))*(b-a);
}

void pivotement(vector<double> &Delta, int dim)
{
    Delta.clear();
	for (int i = 0; i < dim; ++i)
	{
		Delta.push_back((proba_alea()-.5)*2);
	}
}
