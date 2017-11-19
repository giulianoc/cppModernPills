#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Dog {
		string name_;
	public:
		Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name; }
		Dog() { cout << "Nameless Dog is create." << endl; name_ = "nameless"; }
		~Dog() { cout << "Dog is destroyed: " << name_ << endl; }
		void bark() { cout << "Dog " << name_ << " rules!" << endl; } 
};

void foo()
{
	// shared_ptr keep tracks about how many shared pointers are pointing
	//	to the object and when number becomes zero, that object will be
	//	deleted automatically
	shared_ptr<Dog> p (new Dog("Gunner"));	// Count = 1
	// it implements 2 steps: 1. Dog is created; 2. p is created

	{
		shared_ptr<Dog> p2 = p;	// Count = 2
		p2->bark();
		
		cout << p.use_count() << endl;
	}
	// Count = 1

	// p can be used as a raw pointer
	p->bark();
	(*p).bark();
	// p can also be casted to a different type of pointer using:
	// static_pointer_cast
	// dynamic_pointer_cast
	// const_pointer_cast
	
}	// Count = 0

int main()
{
	foo();
	
	// next is a very bad way of using the shared_ptr.
	// when p goes out of scope, d will be destroyed and
	// when p2 goes out of scope, d will be destroyed again counsing undefined behaviour
	/*
	Dog* d = new Dog("Tank");
	shared_ptr<Dog> p(d);		// Count = 1
	shared_ptr<Dog> p2(d);		// Count = 1
	*/
	// An object should be assigned to a smart pointer as soon as it is created.
	// Row pointer should not be used again
	auto p = make_shared<Dog>("Tank");	// faster and safer
	// make_shared combines the 2 steps	in one step. 
	// This is important because what if step 1. is successfully (Dog is created)
	// but step 2. has failed to be created. The Dog "Gunner" will not be managed
	// by the shared pointer, therefore it will not be deleted and this memory will be leaked
	// Then
	// shared_ptr<Dog> p (new Dog("Gunner")) 			is NOT exception safe
	// shared_ptr<Dog> p = make_shared<Dog>("Tank") 	is exception safe
	
}
