#include "MyAlgorithm.h"

using std::cout;
using std::setw;
using std::endl;

//-------------------Constructeur / Destructeur --------------------------------

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions(), d_fitnessValues(), d_setup(setup), d_upperCost(), d_lowerCost()
{
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	cout<<"Creation de l'ABC : "<<endl;
	cout<<"Probleme "<<pbm<<endl;

	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm}; //le tableau solution
		//std::cout<<"Initialisation de la d_solutions "<<std::setw(2)<<i<<" avec une taille "<<d_solutions[i]->size()<<endl;
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()}; //index et fitness du tableau
	}
	trier();
}

ABC::~ABC()
{
	for(int i=0;i<d_solutions.size();++i)
	{
		delete d_solutions[i];
	}
}

//--------------------------Surcharge-----------------------------

std::ostream& operator<<(std::ostream& os, const ABC& myAlgo)
{
    for(int i{} ; i < myAlgo.d_solutions.size() ; ++i)
        os << *(myAlgo.d_solutions[i]) << "\n";
    for(int i{} ; i < myAlgo.d_fitnessValues.size() ; ++i)
        os << myAlgo.d_fitnessValues[i].index << " : " << myAlgo.d_fitnessValues[i].fitness << "\n";
    os << myAlgo.d_setup << "\n" << myAlgo.d_upperCost << " " << myAlgo.d_lowerCost;
    return os;
}

//-----------------Get----------------------------------------

const vector<Solution*>& ABC::solutions() const	{return d_solutions;}
vector<struct particle>&  ABC::fitness_values()	{return d_fitnessValues;}
Solution& ABC::solution(const int index) const	{return *(d_solutions[index]);}
double ABC::fitness(const int index) const		{return d_fitnessValues[index].fitness;}
int ABC::upper_cost() const		{return d_upperCost;}											//Tableau trié ->d_setup.population_size()-1 
int ABC::lower_cost() const		{return d_lowerCost;}											//Tableau trié ->0
double ABC::best_cost()  const	{return fitness(lower_cost());}
double ABC::worst_cost() const	{return fitness(upper_cost());}
Solution& ABC::best_solution()  const	{return solution(best_cost());}
Solution& ABC::worst_solution() const	{return solution(worst_cost());}
const SetUpParams& ABC::setup() const	{return d_setup;}

//-----------------Boucle---------------------------------------

void ABC::evolution()
{
	for (int i=0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		for (int j=0;j<d_setup.nb_evolution_steps();++j)
		{
			evaluate();
			//Evaluate jusqu'à d_setup.nb_evolution_steps() ou fitness = 0
		}
		std::cout << "Iteration n"<<std::setw(2)<<i+1<<" -> meilleur solution : "<<std::setw(8)<<best_cost()<< " pire solution : "<<std::setw(8)<<worst_cost()<<std::endl;
	}
}

void ABC::initialize()
{
	for(int i=0;i<d_solutions.size();++i)
    {
        d_solutions[i]->initialize();
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()};
    }
    trier();
}

void ABC::evaluate()
{
	trier();
    int m=d_solutions.size()/2;
    //for (int i = 0; i < m; ++i)
    {
        //delete d_solutions[i+m];
        //d_solutions[i+m]=new Solution(*d_solutions[i]);
    }
    d_upperCost = d_fitnessValues.size()-1;
    d_lowerCost = 0;
    //CalculateProbabilities();
	//Revoir
}

std::vector <int> ABC::CalculateProbabilities() const
{
	std::vector <int> t;
	t.resize(d_setup.population_size());
	
	for (int i=0; i<d_setup.population_size(); ++i)
	{
		double maxsol=d_solutions[i]->maxSol();
		std::cout<<"Abeille "<<std::setw(3)<<i<<" avec le max "<<maxsol<<std::endl;
		
		for (int j=0; j<d_setup.solution_size(); ++j)
		{
			std::cout<<'\t'<<"Regarde a la position "<<std::setw(3)<<j<<'\t'<<d_solutions[i]->position(j);
			double r = rand()%1000/1000.0;
			if (r<0.9 * d_solutions[i]->position(j)/maxsol+0.1)
			{
				t[i]=j;
				std::cout<< " et la choisi"<<std::endl;
				//j=d_setup.solution_size();
			}
			else std::cout<<" et la choisi pas"<<std::endl;
		}
		std::cout<<"La meilleur sol est : "<<maxsol<<std::endl;
	}
	return t;
}

//-------------------Fonction de Tri-----------------------------

void ABC::trier()
{
	QuickSort(0,d_setup.population_size());
	d_lowerCost=0;
	d_upperCost=d_setup.population_size()-1;
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

void ABC::QuickSort(int gauche, int droite)
{
	int r;
    if(gauche<droite)
    {
        r=partition(gauche,droite);
        QuickSort(gauche,r);  
        QuickSort(r+1,droite);
    }
}
