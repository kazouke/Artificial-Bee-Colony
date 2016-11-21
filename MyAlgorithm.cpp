#include "MyAlgorithm.h"

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

void ABC::trier()
{
    int indice = -1;
    for(unsigned int i=0; i<d_solutions.size(); ++i)
    {
        indice=imin(i);
        if(indice != i)
        {
            std::swap(d_solutions[i],d_solutions[indice]);
            std::swap(d_fitnessValues[i].index,d_fitnessValues[indice].index);
        }
    }
}

ABC::ABC(const Problem& pbm,const SetUpParams& setup):d_solutions(), d_fitnessValues(), d_setup(setup), d_upperCost(), d_lowerCost()
{
	for(unsigned int i=0;i<d_setup.population_size();++i)
    {
        d_solutions.push_back(new Solution(pbm));
        d_fitnessValues.push_back(particle {.index=i,
                                            .fitness=d_solutions.back()->fitness()});
    }
	trier(); //trie les solutions par rapport à la fitness, croissant
}

ABC::~ABC()
{
	for(int i=0;i<d_solutions.size();++i)
	{
		delete d_solutions[i];
	}
}

void ABC::launch()
{
	//Fonction utilisée pour les tests mais qui sera la boucle principale
	
	std::cout << "Tableau des fitness trie : " << std::endl;
	trier();
	for(int i=0; i < d_fitnessValues.size();i++)
	{
		std::cout << "Valeur " << i+1 <<" : fitness  : " << d_fitnessValues[i].fitness << " a la case " << d_fitnessValues[i].index << std::endl;
	}
	
}


