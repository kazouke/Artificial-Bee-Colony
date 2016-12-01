#ifndef SOLUTION_H
#define SOLUTION_H
#include <iostream>
#include <vector>
#include "Problem.h"
class Solution
  {
  	//class Problem;
	//contient la déclaration d'une solution
	public:
		Solution (const Problem& pbm);
		Solution (const Solution& sol);
		~Solution();

 		friend std::ostream& operator<< (std::ostream& os, const Solution& sol);
		friend std::istream& operator>> (std::istream& is, Solution& sol);

		const Problem& pbm() const;

		Solution& operator= (const Solution& sol);
		bool operator== (const Solution& sol) const;
		bool operator!= (const Solution& sol) const;

		void initialize(); // nourriture à initialiser = lower limit + rand(0,1) * (upper limit - lower limit)
		double fitness();

		unsigned int size() const;
		double maxSol() const;

		std::vector<double>& solution();

		double position(const int index); //retournera une position du tableau _solution
        void position(const int index, const double value);


	private:
        std::vector<double> _solution;
        double _current_fitness;
		const Problem& _pbm;
  };

#endif
