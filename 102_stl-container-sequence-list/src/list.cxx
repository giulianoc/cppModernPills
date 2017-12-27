#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
    // list is a double linked list

    // Properties of the list:
    //  1. fast insert-remove at any place: O(1)
    //  2. slow search: O(n)
    //      This is much slower than the vector because of locality.
    //
    //      - Vector stores data in contiguous chunk of memory, it means when the memory is swapped
    //      into cache, it is more likely you have every item in the cache, cache loves contiguous
    //      memory of data.
    //      On the other hand, every element of a list is stored in a different place of the memory,
    //      so when the list is traversed, we will have a lot of cache missed and we will end up to swap
    //      data in and out of cache
    //      - A list consumes more memory than a vector because of the two pointers for every item. And more memory
    //      means more cache missed and more page swap.
    //  3. no ramdom access, no [] operator
    //  4. list has the 'splice' method that does not have any other container: O(1) indipendently by the size of the chunk of data

    list<int> mylist1 = { 5, 2, 9 };
    mylist1.push_back(6);                                               // mylist1: { 5, 2, 9, 6 }
    mylist1.push_front(4);                                              // mylist1: { 4, 5, 2, 9, 6 }

    list<int>::iterator itr = find(mylist1.begin(), mylist1.end(), 2);  // itr -> 2
    mylist1.insert(itr, 8);                                             // mylist1: { 4, 5, 8, 2, 9, 6 }
    itr++;                                                              // itr -> 9
    mylist1.erase(itr);                                                 // remove by position,, mylist1: { 4, 5, 8, 2, 6 }
    mylist1.remove(5);                                                  // remove by value, mylist1: { 4, 8, 2, 6 }
    itr = find(mylist1.begin(), mylist1.end(), 8);                      // itr -> 8

    {
        list<int> mylist2 = { 10, 20, 30, 40, 50, 60, 70};
        list<int>::iterator itr1 = find(mylist2.begin(), mylist2.end(), 30);
        list<int>::iterator itr2 = find(mylist2.begin(), mylist2.end(), 60);

        mylist1.splice(itr, mylist2, itr1, itr2);    // mylist1 = { 4, 30, 40, 50, 8, 2, 6}, mylist2 = {10, 20, 60, 70 }

        for (int i: mylist1)
            cout << i << " ";
        cout << endl;
        for (int i: mylist2)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}
