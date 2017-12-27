#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Dog {
private:
    // shared_ptr<Dog> m_pFriend;	// cyclic reference --> memory leaks (none of Dog will be deleted) 

    // weak_ptr has no ownership of the pointed object.
    // weak_ptr is similar to have a Dog* but it provides some protections:
    //	- no one can perform delete of the pointer
    //	- safe access to the pointer (see the lock() description below)
    weak_ptr<Dog> m_pFriend;	
    string name_;
public:
    Dog(string name) { cout << "Dog is created: " << name << endl; name_ = name; }
    Dog() { cout << "Nameless Dog is create." << endl; name_ = "nameless"; }
    ~Dog() { cout << "Dog is destroyed: " << name_ << endl; }
    void bark() { cout << "Dog " << name_ << " rules!" << endl; }
    void makeFriend(shared_ptr<Dog> f) { m_pFriend = f; }
    void showFriend() {
        // lock() creates a shared_ptr out of the weak_ptr to make sure:
        //	- check if the weak_pointer is still pointing to a valid object
        //	- make sure that while it is accessing the object, it will not be deleted
        // If the weak_ptr is a null pointer, lock() will generate an exception. To avoid that we could add the expired() check
        if (!m_pFriend.expired())
                cout << "My friend is: " << m_pFriend.lock()->name_ << endl;
        // use_count() returns how many shared_ptr are pointing to that object
        cout << "He is owned by " << m_pFriend.use_count() << " pointers." << endl;
    }
};

int main()
{
    auto pD = make_shared<Dog>("Gunner");
    auto pD2 = make_shared<Dog>("Smokey");

    pD->makeFriend(pD2);
    pD2->makeFriend(pD);
    pD->showFriend();

}
