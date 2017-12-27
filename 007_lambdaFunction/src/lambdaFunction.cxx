#include <iostream>
#include <vector>

using namespace std;

template<typename func>
void filter(func f, vector<int> arr) {
	for (auto i: arr)
	{
		if (f(i))
			cout << i << " ";
	}
} 

int main()
{
	cout << [](int x, int y) { return x + y; }(3,4) << endl;
	
	auto f = [](int x, int y) { return x + y; };
	
	cout << f(3,4) << endl;
	
	{
		vector<int> v = { 1, 2, 3, 4, 5, 6 };
		
		filter ([](int x) { return x > 3; }, v);
		cout << endl;
		filter ([](int x) { return x > 2 && x < 5; }, v);
		
		cout << endl;
		int y = 4;
		filter([&](int x){return x > y;}, v);   // & to have access to local variables by the lambda function

		cout << endl;
	}
}
