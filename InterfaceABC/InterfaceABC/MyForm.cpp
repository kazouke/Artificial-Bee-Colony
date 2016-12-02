#include <iostream>
#include <ctime>
#include "Solution.h"
#include "Problem.h"
#include "SetUpParams.h"
#include "bench.h"
#include "MyAlgorithm.h"
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

void InterfaceABC::MyForm::CreerSetUp(int nbRuns, int nbEvoSteps, int popSize, int solSize) {
	SetUpParams sup{ nbRuns, nbEvoSteps, popSize, solSize };
	//Test de la construction de SetUpParams réussi :
	textBox3->Text = "Nombre de runs : " + sup.independent_runs() + "\n Nombre d'étapes d'évolution : " + sup.nb_evolution_steps() + "\n Taille de la population : " + sup.population_size() + "\n Taille de la solution : " + sup.solution_size();
}

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceABC::MyForm);
	srand(time(0));
}

