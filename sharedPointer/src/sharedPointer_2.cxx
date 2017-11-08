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
    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner");    // using default deleter: operator delete
    shared_ptr<Dog> p2 = make_shared<Dog>("Tank");

    // Gunner is deleted if
    // p1 = p2;    or
    // p1 = nullptr;   or
    // p1.reset();

    // Custom deleter (in this case, only in this case, we can't use make_shared)
    shared_ptr<Dog> p3 = shared_ptr<Dog>(new Dog("Tank2"),
                                         [](Dog* p) { cout << "Custom deleting. "; delete p; }
                                         );

    // in one scenario the custom deleter is mandatory: when an array is allocated.
    // In case we do not set a custom deleter, we would have a memory leaks because only the first Dog would be deleted
    shared_ptr<Dog> p4(new Dog[3], [](Dog* p) { delete[] p;});

    // share_ptr has a method get returning the raw pointer but, absolutely we do not have to use it because
    //  in case it is done delete d; when p1 will go out of scope ...
    //  in case it is done shared_ptr<Dog> p5(d); when p1 will go out of scope ...
    //  in case it is done doghouse.saveDog(d); when p1 will go out of scope ...
    Dog* d = p1.get();
}

int main()
{
	foo();

}
