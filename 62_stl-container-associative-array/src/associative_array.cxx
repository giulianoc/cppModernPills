#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int foo (const unordered_map<char, string> &m)
{
    // m['M'] = "MONDAY";           compiler error because m is declared as const
    // cout << m['M'] << endl;      compiler error because the subscript operator provides a write access to the container
    auto itr = m.find('M');
    if (itr != m.end())
        cout << (*itr).first << " " << (*itr).second << endl;
}

int main()
{
    // There is no separate container for an associative array because it can be implemented with map or unordered_map

    // Properties of an associated array:
    //  1. Search time: unordered_map, O(1); map: O(log(n))
    //  2. unordered_map may degrade to O(n)
    //  3. can't use unordered_multimap and multimap, they do not have the [] operator

    unordered_map<char, string> day = { { 'S', "Sunday" }, { 'M', "Monday" } };

    cout << day['S'] << endl;               // no range check
    cout << day.at('S') << endl;            // Has range check

    vector<int> vec = {1, 2, 3};
    vec[5] = 5;     // it should not compile but on linux/g++ it compiles

    for (auto i: vec)
        cout << i << " ";
    cout << endl;

    // next statement is the same day.insert(...)
    day['W'] = "Wednesday";                 // Inserting { 'W', "Wednesday" }
    day.insert(make_pair('F', "Friday"));   // Inserting { 'F', "Friday" }

    // however, day.insert cannot be used to modify an existing element in the container
    day.insert(make_pair('M', "MONDAY"));   // Fail to modify, it's an unordered_map
    // the subscript operator (this is how the [] operator is called) can be used to modify an existing member
    day['M'] = "MONDAY";                    // Succeed to modify

    foo(day);

    return 0;
}
