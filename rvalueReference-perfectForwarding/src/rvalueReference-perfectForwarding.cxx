#include <iostream>

using namespace std;

// huge class (array)
class BoVector {
	int size;
	double *arr_;	// a big array
	
	public:
		BoVector (int size)
		{
			this -> size = size;
			arr_ = new double[size];
		}
		
		BoVector(const BoVector& rhs)	// Copy constructor (very costly deep copy)
		{
			size = rhs.size;
			arr_ = new double[size];
			for (int i = 0; i < size; i++)
			{
				arr_[i] = rhs.arr_[i];
			}
		}
		
		BoVector(BoVector&& rhs)	// Move constructor (inexpensive shallow copy)
		{
			size = rhs.size;
			arr_ = rhs.arr_;
			
			rhs.arr_ = nullptr;
		}

		~BoVector() { delete arr_; }
};

// BoVector has both move and copy constructor defined
void foo (BoVector v) { };

BoVector createBoVector() { return BoVector(100000); };	// creates a BoVector

template <typename T>
void relay(T&& arg)
{
	foo(std::forward<T>(arg));
}
/*
	In order to have that:
	- when relay(reusable) is called, since reusable is a lvalue, copy constructor is invoked 
	- when relay(createBoVector()) is called, since createBoVector() is a rvalue, move constructor is invoked
	we have to declare the relay argument as T&& and std::forward has to be used.
	To understand the reason of that:
	
	Reference collapsing rules:
		1. T& & ---> T&
	 	2. T& && --> T&
	 	3. T&& & --> T&
	 	4. T&& && -> T&&
	
	T&& is Universal Reference if:
	* T is a template type
	* T is a function template type, not class template type
	
	std::move() vs std::forward()
	* std::move<T>(arg);	// Turn arg into a rvalue type
	* std::forward<T>(arg)	// Turn arg to type of T&&
 */

int main()
{
		BoVector reusable = createBoVector();
		relay(reusable);			// lvalue -> copy constructor has to be invoked
		// ...
		relay(createBoVector());	// rvalue -> move constructor has to be invoked
}
