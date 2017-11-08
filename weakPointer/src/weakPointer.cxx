#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Dog {
        shared_ptr<Dog> m_pFriend;
		string name_;
	public:
		Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name; }
		Dog() { cout << "Nameless Dog is create." << endl; name_ = "nameless"; }
		~Dog() { cout << "Dog is destroyed: " << name_ << endl; }
		void bark() { cout << "Dog " << name_ << " rules!" << endl; }
        void makeFriend(shared_ptr<Dog> f) { m_pFriend = f; }
};

int main()
{
    shared_ptr<Dog> pD = make_shared<Dog>("Gunner");
    shared_ptr<Dog> pD2 = make_shared<Dog>("Smokey");

    pD->makeFriend(pD2);
    pD2->makeFriend(pD);

}
