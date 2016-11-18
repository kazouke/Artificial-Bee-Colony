#include "MyAlgorithm.h"

/*ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions(), d_fitnessValues(), d_setup(setup), d_upperCost(), d_lowerCost()
{
	d_solutions.resize(0);
	d_fitnessValues.resize(0);
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm};	//ajoute une solution au problème passé en paramètre
        //d_fitnessValues[i]=particle {.index=i,.fitness=d_solutions.back()->calFitness()};	//ajoute la fitness de la dernière solution
	}
	trier(d_fitnessValues,d_solutions); //trie les solutions par rapport à la fitness, croissant
}

ABC::~ABC()
{
	for(int i=0;i<d_solutions.size();++i)
	{
		delete d_solutions[i];
	}
}


std::ostream& ABC::operator<<(std::ostream& os, const ABC& myAlgo)
{
    for(int i{} ; i < myAlgo.d_solutions.size() ; ++i)
        os << *(myAlgo.d_solutions[i]) << "\n";
    for(int i{} ; i < myAlgo.d_fitnessValues.size() ; ++i)
        os << myAlgo.d_fitnessValues[i].index << " : " << myAlgo.d_fitnessValues[i].fitness << "\n";
    os << myAlgo.d_setup << "\n" << myAlgo.d_upperCost << " " << myAlgo.d_lowerCost;
    return os;
}

std::istream& ABC::operator>>(std::istream& is, ABC& myAlgo)
{
    is >> myAlgo.d_setup;
    return is;
}

const SetUpParams& ABC::setup() const
{
	return d_setup;
}

void ABC::initialize() //renouvelle les solutions
{
	for(int i=0;i<d_solutions.size();++i)
    {
        delete d_solutions[i];
        d_solutions[i] = new Solution{Problem{d_solutions[i]->pbm()}};
		//Revoir
    }
}
/*
void ABC::evaluate()
{
	trier();
    int m=d_solutions.size()/2;
    for (int i = 0; i < m; ++i)
    {
        delete d_solutions[i+m];
        d_solutions[i+m]=new Solution(*d_solutions[i]);
    }
    d_upperCost = d_fitnessValues.size()-1;
    d_lowerCost = 0;
	//Revoir
}

const vector<Solution*>& ABC::solutions() const
{
	return d_solutions;
}

int ABC::upper_cost() const
{
	return d_upperCost;
}

int ABC::lower_cost() const
{
	return d_lowerCost;
}

Solution& ABC::solution(const int index) const
{
	return *(d_solutions[index]);
}

vector<struct particle>&  ABC::fitness_values()
{
	return d_fitnessValues;
}

double ABC::fitness(const int index) const
{
	return d_fitnessValues[index].fitness;
}

double ABC::best_cost() const
{
	return d_solutions[d_lowerCost]->getFitness();
}

double ABC::worst_cost() const
{
	return d_solutions[d_upperCost]->getFitness();
}

Solution& ABC::best_solution() const
{
	
}

Solution& ABC::worst_solution() const
{
	
}

void ABC::evolution() //evolution(int iter), le nombre d'iteration est dans SetUpParams
{
	for (int i=0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		double fitnessMin=d_solutions[0]->calFitness();
	}
}

void ABC::trier(std::vector<particle> &fitnessValues, std::vector<Solution*> &solutions) //QuickSort
{
    int indice = -1;
    for(int i=0; i<solutions.size(); ++i)
    {
        indice=imin(solutions,i);
        if(indice != i)
        {
            std::swap(solutions[i],solutions[indice]);
            std::swap(fitnessValues[i].index,fitnessValues[indice].index);
        }
    }
}*/
