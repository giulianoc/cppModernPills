

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	// C++ 03
	enum apple {green_a, red_a};
	enum orange {big_o, small_o};
	
	apple a1 = green_a;
	orange o1 = big_o;
	
	// we can compare apple to orange
	if (a1 == o1)
		cout << "green apple and big orange are the same" << endl;
	else
		cout << "green apple and big orange are not the same" << endl;


	// C++ 11
	enum class newapple {green, red};
	enum class neworange {big, small};
	
	
	newapple a2 = newapple::green;
	neworange o2 = neworange::big;
	// compile error because we haven't define the == between newapple and neworange
	// if (a2 == o2)
		cout << "green apple and big orange are the same" << endl;
	// else
		cout << "green apple and big orange are not the same" << endl;
	

	return 0;
}
