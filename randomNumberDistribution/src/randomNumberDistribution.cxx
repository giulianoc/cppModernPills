#include <random>
#include <iostream>

using namespace std;

int main()
{
	default_random_engine e;
	
	uniform_int_distribution<int> distr(0, 5);	// Random in range: [0, 5]
	cout << distr(e) << endl;
	
	uniform_real_distribution<double> distrR(0, 5);	// Random in range: [0, 5)	half open, 5 is not included
	cout << distrR(e) << endl;

	poisson_distribution<int> distrP(1.0);	// mean
	cout << distrP(e) << endl;

	cout << " normal distribution: " << endl;
	normal_distribution<double> distrN(10.0, 3.0);	// mean and standard deviation
	vector<int> v(20);
	for (int i = 0; i < 800; i++)
	{
		int num = distrN(e);		// convert double to int
		if (num >= 0 && num < 20)
			v[num]++;				// e.g: v[10] records number of times 10 appeared
	}
	for (int i = 0; i < 20; i++)
	{
		cout << i << ": " << string(v[i], '*') << endl;
	}
	cout << endl;
	
	// random number library provides a number of different distributions (poisson, exponential, gamma, ...)
	
	return 0;
}
