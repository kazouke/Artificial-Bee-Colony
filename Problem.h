#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>

class Problem
{
public:
	Problem();
	~Problem();

	friend std::ostream& operator<< (std::ostream& os, const Problem& pbm);
	friend std::istream& operator>> (std::istream& is, Problem& pbm);

	Problem& operator=  (const Problem& pbm);
	bool operator== (const Problem& pbm) const;
	bool operator!= (const Problem& pbm) const;

	//Direction direction () const; //Maximize or Minimize
	int dimension() const;
	double LowerLimit, UpperLimit;

	private:

		int _dimension;
};

#endif
