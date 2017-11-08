#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Dog {
		string name_;
	public:
		Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name; }
		Dog() { cout << "Nameless Dog is create." << endl; name_ = "nameless"; }
		~Dog() { cout << "Dog is destroyed: " << name_ << endl; }
		void bark() { cout << "Dog " << name_ << " rules!" << endl; }
};


// - unique pointer: exclusive ownership (one object can be owned only by one unique pointer)
// - when the unique pointer goes out of scope or it starts to own another object 
//		then the original object will be automatically deleted
// - unique pointer is a light weight smart pointer (it is less expensive to use than a shared pointer)
//		So if you have a lot of shared_ptr that are not shared, it is preferred to use a unique pointer

void test()
{
	unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
	
	pD->bark();
	
	// release(): return the raw pointer and pD gives up the ownership of the Dog,
	//	so nobody own the Dog anymore and nobody automatically delete the Dob anymore
	//	p should be deleted manually or we will have a memory leaks
	// Dog* p = pD.release();
	
	// reset will first destroy Gunner, so no memery leaks
	pD.reset(new Dog("Smokey"));
	if (!pD)
	{
		cout << "pD is empty" << endl;
	}
	else
	{
		cout << "pD is not empty" << endl;
	}
	
	// reset will destroy Smokey, so no memery leaks
	pD.reset();		// same as pD = nullptr;
	if (!pD)
	{
		cout << "pD is empty" << endl;
	}
	else
	{
		cout << "pD is not empty" << endl;
	}
}

void test2()
{
	unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
	unique_ptr<Dog> pD2 = make_unique<Dog>("Smokey");
	
	pD2->bark();
	
	// move() transfers the ownership from one unique pointer to another unique pointer
	pD2 = move(pD);	// move Gunner from pD to pD2
	// 1. Smokey is destroyed
	// 2. pD becomes empty
	// 3. pD2 owns Gunner
	
	pD2->bark();

}

void f(unique_ptr<Dog> p)
{
	p->bark();
	
	// Remark: Gunner is destroyed here and not in test3 function
	//	that because in test3 we have used the move function to move
	//	the Dog from pD to p, so pD is not the owner of Gunner anymore
	//	and p is the only owner of Gunner
}

unique_ptr<Dog> getDog()
{
	unique_ptr<Dog> p = make_unique<Dog>("Smokey");
	
	return p;	// return p by value --> this automatically use the move semantics
}

void test3()
{
	unique_ptr<Dog> pD = make_unique<Dog>("Gunner");
	
	f(move(pD));	
	
	unique_ptr<Dog> pD2 = getDog();
	// Remark: Smokey is destroyed here (same as above remark)
}

void test4()
{
	// in case of a shared pointer, if we have an array of objects, we have to use a custom deleter
	// BUT in case of a unique pointer this is not needed because it is partially specialized for array:
	unique_ptr<Dog[]> dogs(new Dog[3]);
}

int main()
{
	test();
	cout << endl;
	test2();
	cout << endl;
	test3();
	cout << endl;
	test4();
}
