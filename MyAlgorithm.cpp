#include "MyAlgorithm.h"

#define random rand()%1000/1000.0

using std::cout;
using std::setw;
using std::endl;

#define TEST_LEVEL 1

//-------------------Constructeur / Destructeur --------------------------------

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions{}, d_fitnessValues{}, d_setup{setup}, d_upperCost{}, d_lowerCost{}
{
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	if (TEST_LEVEL>=2) cout<<"--------------Initialisation----------------"<<endl;
	if (TEST_LEVEL>=2) cout<<"Creation de l'ABC : "<<endl;
	if (TEST_LEVEL>=2) cout<<pbm<<endl;
	if (TEST_LEVEL>=2) cout<<d_setup<<endl;
	
	for(int i=0;i<d_setup.population_size();++i)
	{
		d_solutions[i]=new Solution{pbm}; //le tableau solution
		//std::cout<<"Initialisation de la d_solutions "<<std::setw(2)<<i<<" avec une taille "<<d_solutions[i]->size()<<endl;
        d_fitnessValues[i]=particle {i,d_solutions[i]->fitness()}; //index et fitness du tableau
	}
	trier();
	if (TEST_LEVEL>=2) cout<<"------------Fin Initialisation--------------"<<endl;
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
	double moyennem=0,moyennep=0;
	for (int i=0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		for (int j=0;j<d_setup.nb_evolution_steps() && best_cost()>0;++j)
		{
    		trier();
    		sendEmployedBees();
			trier();
    		SendOnLookerBees(CalculateProbabilities());
    		trier();
			//Evaluate jusqu'à d_setup.nb_evolution_steps() ou fitness = 0
		}
		trier();
		if (TEST_LEVEL>=1) std::cout << "Iteration n"<<std::setw(2)<<i+1<<" -> meilleur solution : "<<std::setw(8)<<best_cost()<< " pire solution : "<<std::setw(8)<<worst_cost()<<std::endl;
		moyennem+=best_cost()/d_setup.independent_runs();
		moyennep+=worst_cost()/d_setup.independent_runs();
	}
	cout<<"Moyenne = \t\t\t"<<std::setw(13)<<moyennem<<"\t\t"<<std::setw(14)<<moyennep<<endl;
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
    trier();
    if (TEST_LEVEL>=2) cout<<"--------------Fin Initialize----------------"<<endl;
}

void ABC::sendEmployedBees()
{
	if (TEST_LEVEL>=2) cout<<"----------------SendEmployedBees-----------------"<<endl;
	for (int i=0;i<d_setup.population_size();i++)
	{
		if (TEST_LEVEL>=2) cout<<"On regarde l'abeille "<<i+1;
		Solution* newsol= new Solution{*d_solutions[i]};
        /*The parameter to be changed is determined randomly*/
        int param2change=random*(d_setup.solution_size()-1);
        if (TEST_LEVEL>=2) cout<<" on choisit sa source "<<param2change+1<<endl;
        /*A randomly chosen solution is used in producing a mutant solution of the solution i, different from i*/
        int neighbour=random*(d_setup.population_size()-1);
		while(neighbour==i) neighbour=random*(d_setup.population_size()-1);
		if (TEST_LEVEL>=2) cout<<"\tOn choisit l'abeille voisine "<<neighbour+1<<endl;	
		
		//On change une source à la place param2change dans newsol avec une nouvelle valeur
        //Nouvelle valeur = Ancienne + ou - diff * rand
        newsol->position(param2change,newsol->position(param2change)+(newsol->position(param2change)-d_solutions[neighbour]->position(param2change))*(random-0.5)*2);
        //if generated parameter value is out of boundaries, it is shifted onto the boundaries
        double lb= newsol->pbm().lowerLimit();
        double ub= newsol->pbm().upperLimit();
		if (newsol->position(param2change)<lb) newsol->position(param2change, lb);
		if (newsol->position(param2change)>ub) newsol->position(param2change, ub);
		
      	/*double ObjValSol=function(*newsol);
		double FitnessSol=CalculateFitness(ObjValSol);*/
		double FitnessSol=newsol->fitness();
        
        if (TEST_LEVEL>=2) cout<<"\tFitness L'abeille d'origine avait "<<d_fitnessValues[i].fitness<<endl;
        if (TEST_LEVEL>=2) cout<<"\t\tFitness nouvelle solution "<<FitnessSol<<endl;
        
        //a greedy selection is applied between the current solution i and its mutant
	    if (FitnessSol<d_fitnessValues[i].fitness)
	    {
	        //If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i
			//d_solutions[i]->trial=0;
        	delete d_solutions[i];
	        d_solutions[i]=newsol;
	        newsol=nullptr;
	        
	        d_fitnessValues[i].fitness=FitnessSol;
	        if (TEST_LEVEL>=2) cout<<"\tLa nouvelle solution est << meilleure >> !"<<endl;
	    }
        else
	    {
	    	if (TEST_LEVEL>=2) cout<<"\tLa nouvelle solution est moins bonne."<<endl;
			//if the solution i can not be improved, increase its trial counter
	        //d_solutions[i]->trial+=+1;
	    }
		delete newsol;
    }
		trier();
		if (TEST_LEVEL>=2) cout<<"-------------SendEmployedBees FIN----------------"<<endl;
}

void ABC::SendOnLookerBees(std::vector <int> probabilite)
{
	if (TEST_LEVEL>=2) cout<<"----------------SendOnLookerBees-----------------"<<endl;
	for (int i=0;i<d_setup.population_size();i++)
	{
		if (TEST_LEVEL>=2) cout<<"On regarde l'abeille "<<i+1;
		Solution* newsol= new Solution{*d_solutions[i]};
        /*The parameter to be changed is determined randomly*/
        int param2change=probabilite[i];
        if (TEST_LEVEL>=2) cout<<" on choisit sa source "<<param2change+1<<endl;
        /*A randomly chosen solution is used in producing a mutant solution of the solution i, different from i*/
        int neighbour=random*(d_setup.population_size()-1);
		while(neighbour==i) neighbour=random*(d_setup.population_size()-1);
		if (TEST_LEVEL>=2) cout<<"\tOn choisit l'abeille voisine "<<neighbour+1<<endl;	
		
		//On change une source à la place param2change dans newsol avec une nouvelle valeur
        //Nouvelle valeur = Ancienne + ou - diff * rand
        newsol->position(param2change,newsol->position(param2change)+(newsol->position(param2change)-d_solutions[neighbour]->position(param2change))*(random-0.5)*2);
        //if generated parameter value is out of boundaries, it is shifted onto the boundaries
        double lb= newsol->pbm().lowerLimit();
        double ub= newsol->pbm().upperLimit();
		if (newsol->position(param2change)<lb) newsol->position(param2change, lb);
		if (newsol->position(param2change)>ub) newsol->position(param2change, ub);
		
      	/*double ObjValSol=function(*newsol);
		double FitnessSol=CalculateFitness(ObjValSol);*/
		double FitnessSol=newsol->fitness();
        
        if (TEST_LEVEL>=2) cout<<"\tFitness L'abeille d'origine avait "<<d_fitnessValues[i].fitness<<endl;
        if (TEST_LEVEL>=2) cout<<"\t\tFitness nouvelle solution "<<FitnessSol<<endl;
        
        //a greedy selection is applied between the current solution i and its mutant
	    if (FitnessSol<d_fitnessValues[i].fitness)
	    {
	        //If the mutant solution is better than the current solution i, replace the solution with the mutant and reset the trial counter of solution i
	        
			//trial[i]=0;					A revoir
        	
			delete d_solutions[i];
	        d_solutions[i]=newsol;
	        newsol=nullptr;
	        
	        d_fitnessValues[i].fitness=FitnessSol;
	        if (TEST_LEVEL>=2) cout<<"\tLa nouvelle solution est meilleure !"<<endl;
	    }
        else
	    {
	    	if (TEST_LEVEL>=2) cout<<"\tLa nouvelle solution est moins bonne."<<endl;
			//if the solution i can not be improved, increase its trial counter
	        //trial[i]=trial[i]+1;		A revoir
	    }
		delete newsol;
    }
		trier();
		if (TEST_LEVEL>=2) cout<<"-------------SendOnLookerBees FIN----------------"<<endl;
}

std::vector <int> ABC::CalculateProbabilities() const // A FINIR
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
			if (TEST_LEVEL>=2) std::cout<<"Regarde a la position "<<std::setw(3)<<j<<' '<<std::setw(10)<<d_solutions[i]->position(j)<<' ';
			double r = rand()%1001/1000.0;
			if (TEST_LEVEL>=2) cout<<"Proba : "<<setw(6)<<r<<" / "<<setw(10)<<0.9*d_solutions[i]->position(j)/maxsol+0.1<<' ';
			if (r<0.9 * d_solutions[i]->position(j)/maxsol+0.1)
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
	for (int i=0;i<d_setup.population_size();i++)
	{
		if (d_solutions[i].d_trial > MAX_TRIAL)
		{
			d_solutions[i].initialize();
			d_solutions[i].d_trial = 0;
		}
	}
}

//-------------------Fonction de Tri-----------------------------

void ABC::trier()
{
	QuickSort(0,d_setup.population_size());
	d_lowerCost=0;
	d_upperCost=d_setup.population_size()-1;
	//cout<<"Meilleur = "<<setw(10)<<best_cost()<<endl;
	//cout<<"Pire     = "<<setw(10)<<worst_cost()<<endl;
	//for (int i=0;i<d_setup.population_size();i++) cout<<setw(3)<<i<<'\t'<<d_fitnessValues[i].fitness<<endl;
	
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
