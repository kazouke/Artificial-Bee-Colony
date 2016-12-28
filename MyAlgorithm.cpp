#include "MyAlgorithm.h"
#include "bench.h"

using std::cout;
using std::setw;
using std::endl;

int TEST_LEVEL;

//-------------------Constructeur / Destructeur --------------------------------

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions{}, d_fitnessValues{}, d_setup{setup}, d_upperCost{}, d_lowerCost{}
{
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm};
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()};
	}
}

ABC::~ABC() {for(int i=0;i<d_solutions.size();++i){delete d_solutions[i];}}

//-----------------Get----------------------------------------

const vector<Solution*>& ABC::solutions() const	{return d_solutions;}
vector<struct particle>&  ABC::fitness_values()	{return d_fitnessValues;} //On l'utilise jamais en fait celui-là,du coup a-t-on réellement besoin de particle ?
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

double ABC::evolution()
{
	TEST_LEVEL=0;
	std::fixed;double moyenne=0;double meilleur=INT_MAX;
	for (int i=0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		trier();
		for (int j=0;j<d_setup.nb_evolution_steps() && best_cost()>0;++j)
		{
    		sendEmployedBees();
    		SendOnLookerBees(CalculateProbabilities());
    		trier();
    		sendScoutBees();
		}
		if (TEST_LEVEL>=1) std::cout << "Iteration n"<<std::setw(2)<<i+1<<" -> meilleur solution : "<<std::setprecision(10)<<best_cost();
		moyenne+=best_cost()/d_setup.independent_runs();
		if (meilleur>best_cost())
		{
			cout<<" nouveau meilleur.";
			meilleur=best_cost();
		}
		cout<<std::endl;
	}
	cout<<"Moyenne = "<<std::setprecision(10)<<moyenne<<endl;
	return meilleur;
}

void ABC::initialize()
{
	if (TEST_LEVEL>=2) cout<<"----------------Initialize------------------"<<endl;
	for(int i=0;i<d_solutions.size();++i)
    {
        d_solutions[i]->initialize();
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()};
        if (TEST_LEVEL>=2) cout<<setw(3)<<i+1<<'\t'<<d_fitnessValues[i].fitness<<endl;
    }
    if (TEST_LEVEL>=2) {cout<<"--------------Fin Initialize----------------"<<endl;system("pause");}
}

void ABC::BeesWork(int param2change,int i)
{
	Solution* newsol= new Solution{*d_solutions[i]};
	
	int neighbour=random()*(d_setup.population_size()-1);
	while(neighbour==i) neighbour=random()*(d_setup.population_size()-1);
	
	double x=newsol->position(param2change);
	double y=d_solutions[neighbour]->position(param2change);
	newsol->position(param2change,x+(x-y)*(random()*2-1)*2);
	
	if (newsol->position(param2change)<newsol->pbm().lowerLimit()) newsol->position(param2change, newsol->pbm().lowerLimit());
	if (newsol->position(param2change)>newsol->pbm().upperLimit()) newsol->position(param2change, newsol->pbm().upperLimit());
	
	double FitnessSol=newsol->fitness();
	if (FitnessSol<d_fitnessValues[i].fitness)
	{
		delete d_solutions[i];d_solutions[i]=newsol;newsol=nullptr;
	    d_fitnessValues[i].fitness=FitnessSol;
	}
    else	d_solutions[i]->incrementerTrial();
	delete newsol;
}

void ABC::sendEmployedBees()
{
	if (TEST_LEVEL>=2) cout<<"----------------SendEmployedBees-----------------"<<endl;
	for (int i=0;i<d_setup.population_size();i++)
	{
		//On change un parametre de maniere completement aleatoire
        int param2change=random()*(d_setup.solution_size()-1);
        BeesWork(param2change,i);
    }
	if (TEST_LEVEL>=2) {cout<<"-------------SendEmployedBees FIN----------------"<<endl;system("pause");}
}

void ABC::SendOnLookerBees(std::vector <int> probabilite)
{
	if (TEST_LEVEL>=2) cout<<"----------------SendOnLookerBees-----------------"<<endl;
	for (int i=0;i<d_setup.population_size();i++)
	{
		//On change un parametre choisi par la fonction CalculateProbabilities
        int param2change=probabilite[i];
        BeesWork(param2change,i);
	}
	if (TEST_LEVEL>=2) {cout<<"-------------SendOnLookerBees FIN----------------"<<endl;system("pause");}
}

std::vector <int> ABC::CalculateProbabilities() const
{
	std::vector <int> probabilite;
	probabilite.resize(d_setup.population_size());
	if (TEST_LEVEL>=2) cout<<"--------------CalculateProbabilities-------------"<<endl;
	for (int i=0; i<d_setup.population_size(); ++i)
	{
		double maxsol=d_solutions[i]->maxSol();
		if (TEST_LEVEL>=2) std::cout<<"Abeille "<<std::setw(3)<<i+1<<" avec le max "<<maxsol<<std::endl;
		
		for (int j=0; j<d_setup.solution_size(); ++j)
		{
			double test=0.9 * d_solutions[i]->position(j)/maxsol+0.1; //Il faut aussi valeur absolue avec abs à la place de *-1
			if (test<0) test*=-1;
			
			if (TEST_LEVEL>=2) std::cout<<"Regarde a la position "<<std::setw(3)<<j<<' '<<std::setw(10)<<d_solutions[i]->position(j)<<' ';
			double r = random();
			if (TEST_LEVEL>=2) cout<<"Proba : "<<setw(6)<<r<<" / "<<setw(10)<<test<<' ';
			if (r<test)
			{
				probabilite[i]=j;
				if (TEST_LEVEL>=2) std::cout<< " O"<<std::endl;
				j=d_setup.solution_size();
			}
			else if (TEST_LEVEL>=2) std::cout<<" X"<<std::endl;
		}
		if (TEST_LEVEL>=2) cout<<"-------------------------------------------------"<<endl;
	}
	return probabilite;
}

void ABC::sendScoutBees()
{
	int maxIndex = 0;
	for (int i=1;i<d_setup.population_size();i++)
	{
		if (d_solutions[i]->trial() > d_solutions[maxIndex]->trial())
		{
			maxIndex=i;
		}
	}
	if(d_solutions[maxIndex]->trial()>=d_setup.max_trial())
			d_solutions[maxIndex]->initialize();
}

//-------------------Fonction de Tri-----------------------------

void ABC::trier(){QuickSort(0,d_setup.population_size());d_lowerCost=0;	d_upperCost=d_setup.population_size()-1;}

int ABC::partition(int gauche, int droite)
{   double x=d_fitnessValues[gauche].fitness;
    int i=gauche;int j;
	for(j=gauche+1; j<droite; j++) if (d_fitnessValues[j].fitness<=x){i=i+1;std::swap(d_fitnessValues[i],d_fitnessValues[j]);}
	std::swap(d_fitnessValues[i],d_fitnessValues[gauche]);
    return i;}

void ABC::QuickSort(int gauche, int droite){int r;if(gauche<droite) {r=partition(gauche,droite);QuickSort(gauche,r);QuickSort(r+1,droite);}}
