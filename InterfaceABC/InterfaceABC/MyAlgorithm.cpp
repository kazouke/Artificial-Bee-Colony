#include "MyAlgorithm.h"

double random()
{
	return (double)rand() / (double)RAND_MAX;
}

using std::cout;
using std::setw;
using std::endl;

//-------------------Constructeur / Destructeur --------------------------------

ABC::ABC(const Problem& pbm, const SetUpParams& setup) :d_solutions{}, d_fitnessValues{}, d_setup{ setup }, d_upperCost{}, d_lowerCost{}
{
	d_solutions.resize(d_setup.population_size());
	d_fitnessValues.resize(d_setup.population_size());
	for (int i = 0; i<d_setup.population_size(); ++i)
	{
		d_solutions[i] = new Solution{ pbm };
		d_fitnessValues[i] = particle{ i,d_solutions[i]->fitness() };
	}
}

ABC::~ABC() { for (int i = 0; i<d_solutions.size(); ++i) { delete d_solutions[i]; } }

//-----------------Get----------------------------------------

const vector<Solution*>& ABC::solutions() const { return d_solutions; }
vector<struct particle>&  ABC::fitness_values() { return d_fitnessValues; }
Solution& ABC::solution(const int index) const { return *(d_solutions[index]); }
double ABC::fitness(const int index) const { return d_fitnessValues[index].fitness; }
int ABC::upper_cost() const { return d_upperCost; }											//Tableau tri� ->d_setup.population_size()-1 
int ABC::lower_cost() const { return d_lowerCost; }											//Tableau tri� ->0
double ABC::best_cost()  const { return fitness(lower_cost()); }
double ABC::worst_cost() const { return fitness(upper_cost()); }
Solution& ABC::best_solution()  const { return solution(best_cost()); }
Solution& ABC::worst_solution() const { return solution(worst_cost()); }
const SetUpParams& ABC::setup() const { return d_setup; }

//-----------------Boucle---------------------------------------

double ABC::evolution()
{
	std::fixed; double moyenne = 0; double meilleur = INT_MAX;
	for (int i = 0; i<d_setup.independent_runs(); ++i)
	{
		initialize();
		for (int j = 0; j<d_setup.nb_evolution_steps() && best_cost()>0; ++j)
		{
			sendEmployedBees();
			SendOnLookerBees(CalculateProbabilities());
			trier();
			sendScoutBees();
			cout <<"Run "<<i+1<<" evolution "<<j+1<<std::endl;
		}
		
		moyenne += best_cost() / d_setup.independent_runs();
		if (meilleur>best_cost())	meilleur = best_cost();		//nouveau meilleur
	}
	cout << "Moyenne  = " << std::setprecision(10) << moyenne << endl;
	cout << "Meilleur = " << std::setprecision(10) << meilleur<< endl;
	return meilleur;
}

void ABC::initialize()
{
	for (int i = 0; i<d_solutions.size(); ++i)
	{
		d_solutions[i]->initialize();
		d_fitnessValues[i] = particle{ i,d_solutions[i]->fitness() };
	}
	trier();
}

void ABC::BeesWork(int param2change, int i)
{
	//L'abeille i est copi�
	Solution* newsol = new Solution{ *d_solutions[i] };

	int neighbour = random()*(d_setup.population_size() - 1);
	//Une abeille voisine (diff�rente de celle de base) est choisie
	while (neighbour == i) neighbour = random()*(d_setup.population_size() - 1);

	//La copie de l'abeille i change une de ses sources avec un mixte de sa source et celle de l'abeille voisine
	double x = newsol->position(param2change);
	double y = d_solutions[neighbour]->position(param2change);
	newsol->position(param2change, x + (x - y)*(random() * 2 - 1) * 2);

	//La source / solution doit �tre dans l'intervalle du probl�me
	if (newsol->position(param2change)<newsol->pbm().lowerLimit()) newsol->position(param2change, newsol->pbm().lowerLimit());
	if (newsol->position(param2change)>newsol->pbm().upperLimit()) newsol->position(param2change, newsol->pbm().upperLimit());
	
	//La fitness de la copie de l'abeille avec une nouvelle source est calcul�e
	double FitnessSol = newsol->fitness();
	if (FitnessSol<d_fitnessValues[i].fitness) //Si la nouvelle source est meilleur, la copie remplace l'ancienne
	{
		delete d_solutions[i]; d_solutions[i] = newsol; newsol = nullptr;
		d_fitnessValues[i].fitness = FitnessSol;
	}//Sinon son compteur de non-�volution augmente
	else	d_solutions[i]->incrementerTrial();
	delete newsol;
}

void ABC::sendEmployedBees()
{
	//Pour chaque abeille
	for (int i = 0; i<d_setup.population_size(); i++)
	{
		//On change un parametre de maniere completement aleatoire
		int param2change = random()*(d_setup.solution_size() - 1);
		BeesWork(param2change, i);
	}
}

void ABC::SendOnLookerBees(std::vector <int> probabilite)
{
	//Pour chaque abeille
	for (int i = 0; i<d_setup.population_size(); i++)
	{
		//On change un parametre choisi par la fonction CalculateProbabilities
		int param2change = probabilite[i];
		BeesWork(param2change, i);
	}
}

std::vector <int> ABC::CalculateProbabilities() const
{
	std::vector <int> probabilite;
	probabilite.resize(d_setup.population_size());
	for (int i = 0; i<d_setup.population_size(); ++i)
	{
		double maxsol = d_solutions[i]->maxSol();

		for (int j = 0; j<d_setup.solution_size(); ++j)
		{
			double test = 0.9 * d_solutions[i]->position(j) / maxsol + 0.1;
			if (test<0) test *= -1;

			double r = random();
			if (r<test)
			{
				probabilite[i] = j;
				j = d_setup.solution_size();
			}
		}
	}
	return probabilite;
}

void ABC::sendScoutBees() //Cherche et reinitialise la source qui a le moins evolu� si plus de d_setup.max_trial() (100)
{
	int maxIndex = 0;
	for (int i = 1; i<d_setup.population_size(); i++) if (d_solutions[i]->trial() > d_solutions[maxIndex]->trial()) maxIndex = i;
	if (d_solutions[maxIndex]->trial() >= d_setup.max_trial())	d_solutions[maxIndex]->initialize();
}

//-------------------Fonction de Tri-----------------------------
//------------Tri croissant QuickSort vu en cours----------------

void ABC::trier() { QuickSort(0, d_setup.population_size()); d_lowerCost = 0;	d_upperCost = d_setup.population_size() - 1; }

int ABC::partition(int gauche, int droite)
{
	double x = d_fitnessValues[gauche].fitness;
	int i = gauche; int j;
	for (j = gauche + 1; j<droite; j++) if (d_fitnessValues[j].fitness <= x) { i = i + 1; std::swap(d_fitnessValues[i], d_fitnessValues[j]); }
	std::swap(d_fitnessValues[i], d_fitnessValues[gauche]);
	return i;
}

void ABC::QuickSort(int gauche, int droite) { int r; if (gauche<droite) { r = partition(gauche, droite); QuickSort(gauche, r); QuickSort(r + 1, droite); } }
