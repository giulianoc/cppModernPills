#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // vector is a dynamically allocated contiguous array in memory that grows in one direction

    // Properties of vector:
    //  1. fast insert-remove at the end: O(1)
    //  2. slow insert-remove at the beginning or in the middle: O(n)
    //      That because, in this scenario, all the items, after the inserted item, have to be shifted at the end
    //  3. slow search: O(n)

    vector<int> vec;        // vec.size() == 0
    vec.push_back(4);
    vec.push_back(1);
    vec.push_back(8);       // vec: {4,1, 8};   vec.size() == 3

    // random access to the vector element
    cout << vec[2] << endl;     // 8, no range check by the [] operator
    cout << vec.at(2) << endl;  // 8, throw range_error exception when index is out of range

    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";

    cout << endl;

    // Iterator is faster then random access (previous way to traverse the vector)
    // Iterator is the universal way of traversing a container
    for (vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++)
        cout << *itr << " ";

    // Generally iterators are half-open: [begin, end)

    cout << endl;

    for (auto it: vec)
        cout << it << " ";

    // because memory of array is contiguous, I could use p as a regular array
    int *p = &vec[0];
    p[2] = 6;

    // Common APIs for all the containers
    vec.empty();
    vec.size();
    vector<int> vec2(vec);  // copy costructor
    vec.clear();
    vec2.swap(vec);         // vec2 becomes empty and vec has 3 items


}
