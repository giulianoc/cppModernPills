#include <iostream>
#include <vector>
#include <algorithm>

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

    // push_back vs emplace_back:
    //  Difference 1.
    //  1.1 push_back accepts only objects of the 'type' if the constructor accept more than one argument
    //      When the vector type is a user-defined type:class or structure,and the constructor of the type 
    //      accepts more than one argument,in such case calling the push_back function requires that 
    //      we pass an object of the type. Note this is only when the constructor accept more than one argument.
    //      In constructor accepting only one argument when calling the push_back we can pass the argument 
    //      of the type of the constructor instead of passing the object
    //  1.2 emplace_back accept arguments of the constructor of the type, in calling the emplace_back we can simply 
    //      pass the arguments of the type of the constructor instead of passing the object itself.
    //  Difference 2:Efficiency
    //  2.1 built-in type
    //      If the type is a built-in type there is no difference in efficiency between push_back and emplace_back 
    //      function.
    //  2.2 User-defined type
    //      For class or structure with constructor accepting one argument.Passing a data of the type accepted
    //      by the constructor is more efficient than passing the object of the type.
    //      If we try to append the object-instead of data accepted by the constructor of the class- directly to the
    //      vector,then here a temporary object is created first. After the temporary object creation it is then copied 
    //      into the vector.Here copying of temporary object into the vector storage produce an overhead which decreases 
    //      the efficiency of the code.Note in the first process-passing raw data instead of object of the class- 
    //      there is no copying of data from the temporary storage to the vector storage ,hence the overhead produced 
    //      by this process is eliminated
    vec.emplace_back(9);
    
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
    cout << endl;

    // because memory of array is contiguous, I could use p as a regular array
    int *p = &vec[0];
    p[2] = 6;

    {
        cout << "Removing first option ..." << endl;
        vector<int> vec2 = { 1, 2, 3, 4, 5, 6, 7, 8};
        for (auto itr = vec2.begin(); itr != vec2.end(); )
        {
            if (*itr == 4)
		itr = vec2.erase(itr);	// returns iterator to the next element
            else
		itr++;
        }
        
        for (auto i: vec2)
            cout << i << ", ";
        cout << endl;

        cout << "Removing second option ..." << endl;
        vector<int> vec3 = { 1, 2, 3, 4, 5, 6, 7, 8};
        vec3.erase(
            remove_if(vec3.begin(), vec3.end(), [](int x){ return x == 4; }),
                vec3.end());
        // std::remove_if: Removing is done by shifting (by means of move assignment) the elements 
        //  in the range in such a way that the elements that are not to be removed appear in the beginning of the range
            
        for (auto i: vec3)
            cout << i << ", ";
        cout << endl;
    }
    
    // Common APIs for all the containers
    vec.empty();
    vec.size();
    vector<int> vec2(vec);  // copy costructor
    vec.clear();
    vec2.swap(vec);         // vec2 becomes empty and vec has 3 items


}
