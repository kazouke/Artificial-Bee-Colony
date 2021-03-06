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
using namespace System::IO;

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
	else if (comboBox1->Text == L"Schwefel")
	{
		xmin=-500;
		xmax=500;
		return schwefel;
	}
	else if (comboBox1->Text == L"Schaffer")
	{
		xmin=-100;
		xmax=100;
		return schaffer;
	}
	else if (comboBox1->Text == L"Weierstrass")
	{
		xmin=-10;
		xmax=10;
		return weierstrass;
	}
}

void InterfaceABC::MyForm::CreerSetUp(unsigned int nbRuns, unsigned int nbEvoSteps, unsigned int popSize, unsigned int solSize, unsigned int maxTrial) {
	if (comboBox1->Text != "")
	{
		textBox3->Text = "Veuillez patientez... ";
		Refresh();
		SetUpParams sup{ nbRuns, nbEvoSteps, popSize, solSize, maxTrial};
		int xmin, xmax;
		Fonction F = choixFonction(xmin, xmax);
		Problem P(xmin, xmax, 30, F);
		ABC A{ P, sup };

		freopen("myfile.txt", "w", stdout);
		A.evolution();
		fclose(stdout);

		String^ Readfile = File::ReadAllText("myfile.txt");
		textBox3->Text = Readfile;
	}
}

[STAThread]//leave this as is
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew InterfaceABC::MyForm);
	srand(time(0));
}

