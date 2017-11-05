

#include <iostream>

using namespace std;

void foo(int i) { cout << "foo int" << endl; }
void foo(char *ptr) { cout << "foo char *" << endl; }

int main(int argc, char **argv)
{
	// nullptr will replace NULL in C++ 11

	// foo(NULL);		// Ambiguity and we will have compiler error
	
	// C++ 11
	foo(nullptr);	// call foo(char *);
		
	return 0;
}
