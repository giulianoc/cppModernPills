

#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

int initializerList();
int aggregateInitializer();

int main(int argc, char **argv)
{
	initializerList();

	aggregateInitializer();

	// uniform initialization is because all the three forms of initialization
	//	initializer_list, regular constructor and aggregate use the same syntax: { <parameters> }
	// So in case all the three forms above are defined in a class, which one is used?
	// The uniform initialization order/priority is:
	// 1. initializer_list constructor
	// 2. regular constractor that takes the appropriate parameters
	// 3. aggregate initializer

	class Dog {
		public:

			int age = 0;			// 3rd choice

			Dog(int a)			// 2nd choice
			{
				age = a;
			};

			Dog(const initializer_list<int>& vec)	// 1st choice
			{
				age = *(vec.begin());
			};
	};

	Dog dog{3};

}

int initializerList()
{
	// array:
	int arr[4] = {3, 2, 4, 5};

	cout << endl << "array:" << endl;
	for (auto index = 0; index < 4; index++)
		cout << arr[index] << endl;


	// vector:
	vector<int> v1 = {3, 4, 1, 9};	// calling initializer_list constructor

	cout << endl << "vector:" << endl;
	for (auto value: v1)
		cout << value << endl;


	// define our own initializer_list constructor
	class BoVector {
		vector<int> m_vect;

		public:
			BoVector (const initializer_list<int>& v)
			{
				for (int value: v)
					m_vect.push_back(value);
			}

			vector<int> getVector() { return m_vect; };
	};

	BoVector v2 = {0, 2, 3, 4};
	cout << endl << "v2: " << endl;
	for (auto value: v2.getVector())
		cout << value << endl;

	BoVector v3{0, 2, 3, 4};	// initializer_list constructor is used
	cout << endl << "v3: " << endl;
	for (auto value: v3.getVector())
		cout << value << endl;


	return 0;
}

int aggregateInitializer()
{
	class Dog {
		public:

			int x;
			string y;
			int z;
	};

	Dog dog1 = {5, "Henry", 7};
	Dog dog2 {5, "Henry", 7};


	// designator since C++20 (commented because some compilers do not support it yet)
	/*
	Dog dog3 = {.x = 5, .y = "Henry", .z = 7};

	Dog dog4 = {.x = 5, .z = 7, .y = "Henry" };
	cout << endl << "dog4. " << "x: " << dog4.x << ", y: " << dog4.y << ", z: " << dog4.z << endl;

	Dog dog5 = {.x = 5 };
	cout << endl << "dog5. " << "x: " << dog5.x << ", y: " << dog5.y << ", z: " << dog5.z << endl;
    */


	return 0;
}

