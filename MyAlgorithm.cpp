#include "MyAlgorithm.h"

#define random rand()%1000/1000.0

using std::cout;
using std::setw;
using std::endl;

//-------------------Constructeur / Destructeur --------------------------------

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions{}, d_fitnessValues{}, d_setup{setup}, d_upperCost{}, d_lowerCost{}
{
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	cout<<"--------------Initialisation----------------"<<endl;
	cout<<setw(43)<<"Creation de l'ABC : "<<'-'<<endl;
	cout<<pbm<<endl;
	cout<<d_setup<<endl;
	
	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm}; //le tableau solution
		//std::cout<<"Initialisation de la d_solutions "<<std::setw(2)<<i<<" avec une taille "<<d_solutions[i]->size()<<endl;
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()}; //index et fitness du tableau
	}
	trier();
	cout<<"------------Fin Initialisation--------------"<<endl<<endl;
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
    CalculateProbabilities();
	//Revoir
}

void ABC::sendEmployedBees()
{
	
	for (int i=0;i<d_setup.solution_size();i++)
	{
			
		//	A VOIR (CANCER)
		Solution* newsol= new Solution{*d_solutions[i]};
        /*The parameter to be changed is determined randomly*/
        int param2change=random*d_setup.solution_size();
        
        /*A randomly chosen solution is used in producing a mutant solution of the solution i, different from i*/
        int neighbour=random*d_setup.population_size();
		while(neighbour==i) neighbour=random*d_setup.population_size();

		
		
        //v_{ij}=x_{ij}+\phi_{ij}*(x_{kj}-x_{ij})
        newsol->position(param2change,d_solutions[i]->position(param2change)+(d_solutions[i]->position(param2change)-d_solutions[neighbour]->position(param2change))*(random-0.5)*2);

        //if generated parameter value is out of boundaries, it is shifted onto the boundaries
        double lb= newsol->pbm().lowerLimit();
        double ub= newsol->pbm().upperLimit();
		if (newsol->position(param2change)<lb) newsol->position(param2change, lb);
		if (newsol->position(param2change)>ub) newsol->position(param2change, ub);
		
      	/*double ObjValSol=function(*newsol);
		double FitnessSol=CalculateFitness(ObjValSol);*/
		double FitnessSol=newsol.fitness();
        
        //a greedy selection is applied between the current solution i and its mutant
	    if (FitnessSol>d_fitnessValues[i].fitness)
	    {
	        //If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i
	        
			//trial[i]=0;					A revoir
			delete d_solutions[i];
	        d_solutions[i]=newsol;
	        newsol=nullptr;					//Julien n'y croit pas
	        
	        //f[i]=ObjValSol;				A revoir
	        d_fitnessValues[i].fitness=FitnessSol;
	    }
        /*else
	    {   //if the solution i can not be improved, increase its trial counter
	        //trial[i]=trial[i]+1;		A revoir
	    }*/
		delete newsol;
    }
		trier();
        //end of employed bee phase
}

std::vector <int> ABC::CalculateProbabilities() const
{
	std::vector <int> t;
	t.resize(d_setup.population_size());
	cout<<"--------------CalculateProbabilities-------------"<<endl;
	for (int i=0; i<d_setup.population_size(); ++i)
	{
		double maxsol=d_solutions[i]->maxSol();
		std::cout<<"Abeille "<<std::setw(3)<<i<<" avec le max "<<maxsol<<std::endl;
		
		for (int j=0; j<d_setup.solution_size(); ++j)
		{
			std::cout<<"Regarde a la position "<<std::setw(3)<<j<<' '<<std::setw(10)<<d_solutions[i]->position(j)<<' ';
			double r = rand()%1000/1000.0;
			cout<<"Proba : "<<setw(6)<<r<<" / "<<setw(10)<<0.9*d_solutions[i]->position(j)/maxsol+0.1<<' ';
			if (r<0.9 * d_solutions[i]->position(j)/maxsol+0.1)
			{
				t[i]=j;
				std::cout<< " O"<<std::endl;
				j=d_setup.solution_size();
			}
			else std::cout<<" X"<<std::endl;
		}
		cout<<"-------------------------------------------------"<<endl;
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
