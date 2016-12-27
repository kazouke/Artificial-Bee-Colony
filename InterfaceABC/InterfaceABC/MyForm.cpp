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

Fonction F = somme_ackley;

Fonction InterfaceABC::MyForm::choixFonction(int&xmin, int&xmax)
{
	if (comboBox1->Text == L"Ackley")
	{
		xmin = -32.768;
		xmax = 32.768;
		return somme_ackley;
	}
	else if (comboBox1->Text == L"Rastrigin")
	{
		xmin = -5.12;
		xmax = 5.12;
		return somme_rastrigin;
	}
	else if (comboBox1->Text == L"Rosenbrock")
	{
		xmin = -5;
		xmax = 10;
		return somme_rosenbrock;
	}
}

void InterfaceABC::MyForm::CreerSetUp(unsigned int nbRuns, unsigned int nbEvoSteps, unsigned int popSize, unsigned int solSize) {
	if (comboBox1->Text != "")
	{
		SetUpParams sup{ nbRuns, nbEvoSteps, popSize, solSize };
		int xmin, xmax;
		F = choixFonction(xmin, xmax);
		Problem P(xmin, xmax, 30, F);
		ABC A{ P, sup };
		freopen("myfile.txt", "w", stdout);
		//Test de la construction de SetUpParams réussi :
		textBox3->Text = "Meilleur : " + A.evolution();
		fclose(stdout);
	}
}

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceABC::MyForm);
	srand(time(0));
}

