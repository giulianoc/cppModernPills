#include <iostream>

class Dog {
	
	Dog(int a) {};
	Dog() = default;			// force compiler to generate the default constructor
	Dog (double a) = delete;	// Dog d(2.3); would generate a compiler error
	
	virtual void bark() final;	// no class can override bark()
	
};

constexpr int cubed(int x) { return x * x * x; };

int main()
{
	int y = cubed(222);		// computed at compile time because of constexpr
}
