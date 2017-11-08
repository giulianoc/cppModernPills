#include <iostream>

using namespace std;

int sum (int x, int y) { return x + y; };

int main()
{
	// Definitions:
	// lvalue: an object that occupies some identifiable location in memory
	// rvalue: any object that it is not lvalue
	
	// lvalue examples (most of variables in c++ are lvalue)
	int i;
	int *p = &i;
	
	// rvalue examples
	auto x = 2;			// 2 is rvalue
	auto y = x + 2;		// (x + 2) is rvalue
	auto z = sum(3, 4);	// sum(3, 4) is rvalue
	
	// reference (lvalue reference)
	int a;
	int& r = a;		// r is lvalue reference
}
