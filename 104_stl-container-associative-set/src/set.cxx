#include <iostream>
#include <tuple>
#include <set>

using namespace std;

int main()
{
    // associative container is typically implemented by binary tree
    // it is always sorted. When an item is inserted it is placed in the correct location. When an item is removed, the tree is rearranged so that everything is still in order
    // the item is sorted according a criteria, default criteria is <
    // value of the elements cannot be modified, iterator is a constant iterator

    // set has no duplicated items

    // Properties of the set:
    //  1. Fast search: O(log(n))
    //  2. Traversing is slow (compared to vector) because of locality (see description in list.cxx)
    //  3, No random access, no [] operator



    set<int> myset;
    myset.insert(3);            // myset: {3}
    myset.insert(1);            // myset: {1, 3}, data are automatically sorted
    myset.insert(7);            // myset: {1, 3, 7}

    set<int>::iterator itr;
    itr = myset.find(7);         // itr --> 7
    // Sequence container doesn't even have find() member function because it takes too long to find

    // value of the elements cannot be modified, itr is a constant iterator
    // *itr = 10;       compiler generate an error

    pair<set<int>::iterator, bool> ret;
    // iterator points to either the item been inserted if the insertion successful or the duplicated item in set if the insertion fails
    // bool to specify if the insert is successful or not

    ret = myset.insert(3);      // insertion fails because 3 is already present
    if (ret.second == false)
        itr = ret.first;        // itr --> 3

    myset.insert(itr, 9);       // myset: {1, 3, 7, 9}, The set decide where to place 9. itr is passed as hint to find the location where 9 has to be placed.
                                //  if the hint is good, the time would be reduced from O(log(n)) to O(1)
                                // itr --> 3
    myset.erase(itr);           // myset: {1, 7, 9}

    myset.erase(7);             // myset: {1, 9}
    // None of the sequence containers provide this kind of erase (erase(7)) because it would take too long to erase

    myset.insert(itr, 10);
    myset.insert(itr, 11);
    myset.insert(itr, 12);      // myset: {1, 9, 10, 11, 12}
    
    // erase(itr) invalidate the iterator, so in case of a loop this is the right algorithm
    {
        cout << "removing..." << endl;
        for (auto itr2 = myset.begin(); itr2 != myset.end(); )
        {
            if (*itr2 == 10)
                myset.erase(itr2++);
            else
                itr2++;
        }
        
        for (int i: myset)
            cout << i << ", ";
        cout << endl;
    }
    
	// test confronto tra tuple
	{
		set<tuple<int, string, int>> tupleset;
		tupleset.insert(make_tuple(1, "2", 3)); 
		tupleset.insert(make_tuple(4, "5", 6)); 

		set<tuple<int, string, int>>::iterator it = tupleset.find(make_tuple(4, "5", 6));
		if (it == tupleset.end())
			cout << "tuple 4, \"5\", 6 not found" << endl;
		else
			cout << "tuple 4, \"5\", 6 found" << endl;	// output qui

		it = tupleset.find(make_tuple(4, "7", 6));
		if (it == tupleset.end())
			cout << "tuple 4, \"7\", 6 not found" << endl;	// output qui
		else
			cout << "tuple 4, \"7\", 6 found" << endl;

		it = tupleset.find(make_tuple(4, "5", 7));
		if (it == tupleset.end())
			cout << "tuple 4, \"5\", 7 not found" << endl;	// output qui
		else
			cout << "tuple 4, \"5\", 7 found" << endl;
	}

    return 0;
}
