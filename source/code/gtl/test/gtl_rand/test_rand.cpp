#include "../../include/gtl_rand.h"
#include <iostream>

using namespace std;
using namespace gtl;

int main ()
{
	RandInit (0);

	cout << RandFloat (0.0, 0.5) << endl;
	cout << RandFloat (0.0, 0.5) << endl;
	cout << RandFloat (0.0, 0.5) << endl;
	cout << RandFloat (0.0, 0.5) << endl;
	cout << RandFloat (0.0, 0.5) << endl;
	cout << RandFloat (0.0, 0.5) << endl;

	cout << RandInt (0, 10) << endl;
	cout << RandInt (0, 10) << endl;
	cout << RandInt (0, 10) << endl;
	cout << RandInt (0, 10) << endl;
	cout << RandInt (0, 10) << endl;
	cout << RandInt (0, 10) << endl;
	
	return 0;
}
