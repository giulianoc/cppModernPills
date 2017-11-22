#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <algorithm>


using namespace std;

int main()
{
    // 1. Random access iterator: vector, deque, array (increment, decrement, add/substruct, compare)

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<int>::iterator itr_v1 = vec.begin();
    vector<int>::iterator itr_v2 = vec.begin();

    itr_v1 = itr_v1 + 5;
    itr_v1 = itr_v1 - 4;
    if (itr_v1 > itr_v2)
        --itr_v1;         // faster than itr1++ because ++itr1 does not have to return the value

    ++itr_v2;


    // 2. Bidirectional Iterator: list, set/multiset, map/multimap (increment, decrement, no add/substruct, no compare)

    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int>::iterator itr_l = l.begin();

    ++itr_l;
    --itr_l;



    // 3. Forward Iterator: forward_list (increment, no decrement, no add/substruct, no compare)

    forward_list<int> fl = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int>::iterator itr_fl = fl.begin();

    ++itr_fl;


    // Unordered containers provides at least forward iterator


    // 4. Input iterator: read and process values while iterating forward
    int x = *itr_v1;


    // 5. Output iterator: output values while iterating forward
    *itr_v1 = 100;


    // every container has an iterator and a const_iterator
    set<int> myset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    set<int>::iterator itr_s;
    set<int>::const_iterator citr_s;  // read only access to container element

    for (citr_s = myset.begin(); citr_s != myset.end(); ++citr_s)
        cout << *citr_s << " ";
    cout << endl;


    // for_each(myset.cbegin(), myset.cend(), myFuntion);
    // advance (itr, 5);    itr += 5
    // distance(itr1, itr2)


    // Iterator adaptor (based on predefined iterator) but more powerful
    //  1. Insert iterator
    //  2. Stream iterator
    //  3. Reverse iterator
    //  4. Move iterator


    //  Algorithms

    vector<int>::iterator itr = min_element(vec.begin(), vec.end());

    // algorithm always process ranges in a half open way,
    // so next sort element from the begin to itr, element pointed by itr excluded
    sort(vec.begin(), itr);

    reverse(itr, vec.end());

    // copy(itr, vec.end(), vec2.begin());  vec2 needs to have space for the elements to be copied

    // vector<int>::iterator itr = find_if(vec.begin(), vec.end(), myFunction);




    return 0;

}
