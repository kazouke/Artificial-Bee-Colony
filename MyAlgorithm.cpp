#include "MyAlgorithm.h"

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions(), d_fitnessValues(), d_setup(setup), d_upperCost(), d_lowerCost()
{
	d_solutions.resize(0);
	d_fitnessValues.resize(0);
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm}; //le tableau solution
        d_fitnessValues[i]=particle {.index=i,.fitness=d_solutions[i]->fitness()}; //index et fitness du tableau
	}
	trier();
}

/*
ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions(), d_fitnessValues(), d_setup(setup), d_upperCost(), d_lowerCost()
{
	for(unsigned int i=0;i<d_setup.population_size();++i)
    {
        d_solutions.push_back(new Solution(pbm));
        d_fitnessValues.push_back(particle {.index=i,
                                            .fitness=d_solutions.back()->fitness()});
    }
}
*/
ABC::~ABC()
{
	for(int i=0;i<d_solutions.size();++i)
	{
		delete d_solutions[i];
	}
}


std::ostream& operator<<(std::ostream& os, const ABC& myAlgo)
{
    for(int i{} ; i < myAlgo.d_solutions.size() ; ++i)
        os << *(myAlgo.d_solutions[i]) << "\n";
    for(int i{} ; i < myAlgo.d_fitnessValues.size() ; ++i)
        os << myAlgo.d_fitnessValues[i].index << " : " << myAlgo.d_fitnessValues[i].fitness << "\n";
    os << myAlgo.d_setup << "\n" << myAlgo.d_upperCost << " " << myAlgo.d_lowerCost;
    return os;
}

std::istream& operator>>(std::istream& is, ABC& myAlgo)
{
    //is >> myAlgo.d_setup; Attendre SetUpParams
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

/*void ABC::evaluate()
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
}*/

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
	return d_solutions[d_lowerCost]->fitness();
}

double ABC::worst_cost() const
{
	return d_solutions[d_upperCost]->fitness();
}

/*Solution& ABC::best_solution() const
{
	
}

Solution& ABC::worst_solution() const
{
	
}*/

/*void ABC::evolution() //evolution(int iter), le nombre d'iteration est dans SetUpParams
{
	for (int i=0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		double fitnessMin=d_solutions[0]->calFitness();
	}
}*/

void ABC::trier()
{
	QuickSort(0,d_fitnessValues.size()-1);
	d_lowerCost=0;
	d_upperCost=d_fitnessValues.size()-1;
}

int ABC::partition(int gauche, int droite)
{
    double x=d_fitnessValues[gauche].fitness;
    int i=gauche;
    int j;

    for(j=gauche+1; j<droite; j++)
    {
        if (d_fitnessValues[j].fitness<=x)
        {
            i=i+1;
            std::swap(d_fitnessValues[i],d_fitnessValues[j]);
        }

    }

    std::swap(d_fitnessValues[i],d_fitnessValues[gauche]);
    return i;
}

void ABC::QuickSort(int gauche, int droite) //Tri Quicksort
{
	int r;
    if(gauche<droite)
    {
        r=partition(gauche,droite);
        QuickSort(gauche,r);  
        QuickSort(gauche+1,droite);
    }
}

/*
int ABC::imin(int i) const
{
    int r=i;
    for(unsigned int j=i+1; j<d_solutions.size(); ++j)
    {
        if(d_solutions[j]->fitness() < d_solutions[r]->fitness())
        {
            r=j;
        }
    }
    return r;
}

*/
