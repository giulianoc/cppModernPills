#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // C++ 03:
    cout << "C++ 03:" << endl;
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
        cout << *itr << " ";

    cout << endl;

    // C++ 11:
    cout << "C++ 11:" << endl;
    for (int i: vec)        // works on any class having begin() and end()
        cout << i << " ";   // read only access

    cout << endl;

    for (int& i: vec)
        cout << ++i << " ";        // changes the values in vec because i is a reference (int&). All the values in vec are incremented by 1

    cout << endl;


    return 0;
}
