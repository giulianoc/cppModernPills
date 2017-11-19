

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

	vector<int> vec = {2, 3, 4, 5};
	
	// C++ 03
	cout << "C++ 03: " << endl;
	for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		cout << *it << endl;
		
	// C++ 11
	cout << endl << "C++ 11: " << endl;
	for (auto it = vec.begin(); it != vec.end(); it++)
		cout << *it << endl;
	// or
	for (auto value: vec)
		cout << value << endl;

	auto a = 6; 	// a is an integer
	auto b = 9.6; 	// b is a double
	auto c = b;		// c is a double too
		
	return 0;
}
