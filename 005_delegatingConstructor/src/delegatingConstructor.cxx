#include <iostream>

using namespace std;

/* next Dog delegating constructor works in java but it does not work in c++

class Dog {
	public:
		void Dog () { cout << "first constructor" << endl; };
		void Dog (int a){ Dog(); cout << "second constructor" << endl; }
};

*/

class Dog {
	public:
		Dog () { cout << "first constructor" << endl; };
		Dog(int a) : Dog() { cout << "second constructor" << endl; };
};

int main(int argc, char **argv)
{
	Dog d (10);
	
}

