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
	printf(sup.independent_runs);
	textBox3->Text = "lol";
}

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceABC::MyForm);
	srand(time(0));
}

