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
	Problem P(-5.12, 5.12, 30, somme_rastrigin);
	ABC A{ P, sup };
	//Test de la construction de SetUpParams réussi :
	textBox3->Text = "Meilleur : " + A.evolution(0);
}

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceABC::MyForm);
	srand(time(0));
}

