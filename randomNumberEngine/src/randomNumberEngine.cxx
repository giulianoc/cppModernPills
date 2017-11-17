#include <random>
#include <iostream>
#include <sstream>

// Random Engine library:
//	Stateful (it has internal state) generator that generates random values within predefined min and max
//	Not truely random - pseudorandom
 
using namespace std;

void printRandom(default_random_engine e)
{
	for (auto i = 0; i < 10; i++)
		cout << e() << " ";
	cout << endl;
}

int main()
{
	{
		default_random_engine eng;
		
		cout << "Min: " << eng.min() << endl;
		cout << "Max: " << eng.max() << endl;
		
		
		// eng is a fanctor
		cout << "Random value: " << eng() << endl;
		cout << "Random value: " << eng() << endl;

		stringstream state;
		state << eng;			// save the current state of the eng
		
		cout << "Random value: " << eng() << endl;
		cout << "Random value: " << eng() << endl;

		state >> eng;			// Restore the state
		
		cout << "Random value: " << eng() << endl;
		cout << "Random value: " << eng() << endl;
	}
	
	{
		default_random_engine e1;
		default_random_engine e2;

		// both printRandom will generate the same random number because
		// they will have the same initial state
		printRandom(e1);
		printRandom(e2);
		
		// to have numbers as random as possible
		unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
		default_random_engine e3(seed);
		printRandom(e3);
		
		// different seed means different state, then different random numbers
		e1.seed();		// reset engine e to initial state
		e1.seed(109);	// reset engine e to a state according to seed 109
		e2.seed(109);
		if (e1 == e2)
			cout << " e1 and e2 have the same state" << endl;
			
		vector<int> d = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		shuffle(d.begin(), d.end(), default_random_engine());
		
		// c++11 provides 16 different type of engines having different generators
	}

		
	return 0;
}
