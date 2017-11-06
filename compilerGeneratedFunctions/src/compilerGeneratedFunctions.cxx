#include <iostream>

using namespace std;

/*
	C++ 03:
	1. default constructor (generated only if no constructor is declared by user)
	2. copy constructor (generated only if 3. or 4. or 5. or 6. not declared by user)
	3. copy assignment (generated only if 2. or 4. or 5. or 6. not declared by user)
	4. destructor
	
	C++ 11:
	5. move constructor (generated only if 2. or 3. or 4. or 6. not declared by user)
	6. move assignment operator (generated only if 2. or 3. or 4. or 5. not declared by user)
 */
 
class Dog {
		Dog();
		Dog (const Dog&);
		Dog& operator =(const Dog &);
		~Dog();
		
		Dog(Dog&&);
		Dog& operator =(Dog&&);
};

// compiler generates 1. 2. 3. 4. 5. 6.
class Horse {
	
};

// compiler generates 3. and 4. (3. is deprecated)
class Cat {		
	Cat(const Cat&) {};
};

// compiler generates: 4.
// it's a useful case: an object that can only be moved constructed anc cannot be copied.
// i.e.: mutex or sockets can only be moved and not be copied
class Duck {
	Duck(Duck&&) {};
};

// compiler generates: 4.
class Frog {
		Frog(Frog&&, int = 0) {};	// move constructor because when the the second parameter is not present ...
};

// compiler generates: 1. 2. 3.	(2. and 3. are deprecated)
class Fish {
	~Fish() {};
};

// compiler generates: 1. 2. 4. (2. is deprecated)
class Cow {
	Cow& operator =(const Cow&) = delete;
	
};

void main ()

{
	
}
