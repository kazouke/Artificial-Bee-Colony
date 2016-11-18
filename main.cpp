#include <iostream>
#include "Solution.h"
#include "Problem.h"
#include <ctime>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* Test pour Github - ICI C'EST LE MASTER*/

int main(int argc, char** argv) {
	srand(time(0));
	Problem p{5,10,10};
	Solution s{p};
	s.initialize();
	
	return 0;
}
