#include <iostream>

using namespace std;

void printInt (int& i) { cout << "lvalue reference: " << i << endl; };
void printInt (int&& i) { cout << "rvalue reference: " << i << endl; };


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

void foo (BoVector v) { };

BoVector createBoVector() { return BoVector(100000); };	// creates a BoVector

int main()
{
	// Kind of definition
	{
		auto a = 5;		// a is lvalue
		auto& b = a;		// b is lvalue reference
		// int&& c		// c is rvalue reference
		
		printInt(a);	// call printInt (int& i) because a is lvalue
		printInt(6);	// call printInt (int&& i) because 6 is rvalue
	}

	// here it is highlighted the importance of the rvalue reference
	{
		BoVector reusable = createBoVector();
		foo(reusable);	// reusable is lvalue, it would invoke the costly Copy Constructor but it's ok we want to reuse reusable
		
		foo(createBoVector());	// createBoVector() is rvalue, it would copy the inexpensive Move Constructor
		
		// in case reusable it is not used anymore from here on, we can use
		foo(std::move(reusable));	// it will call the Move Constructor 
	}
		
	return 0;
}
