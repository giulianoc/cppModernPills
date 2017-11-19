#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    // unordered indicates that the order of the elements is not defined and they may change over the time
    // Internally an unordered container is implemented as an hash table (array of linked list).
    //      - Array is also called array of buckets and the linked lists are called entries.
    //      - Each element is used by Hash function to calculate a value and, based on that value,
    //          elements are inserted into entries
    //      - The biggest advantages of this kind of structure is: if we have a fast and effective Hash function,
    //          finding an element in an hash table is very fast taking constant time O(1),
    //          the fastest among all the containers
    //      - This performance may degrade because of the hash collision. this is when many items are inserted in the
    //          same buckets. The worst case is when all the elements are inserted in one bucket. So the performance
    //          is degraded from O(1) to O(n)

    // Properties of unordered containers:
    //  1. Fastest insert-remove at any place: O(1)
    //      Associative containers takes O(log(n))
    //      Vector, deque takes O(n)
    //      List takes O(1) to insert but it requires to have a pointer pointing to the position to insert, O(n) to search
    //  2. Unordered set-multiset: element value cannot be changed
    //  3. Unordered map-multimap: element key cannot be changed

    unordered_set<string> myset = { "red", "green", "blue" };
    unordered_set<string>::const_iterator itr = myset.find("green");
    if (itr != myset.end())
        cout << (*itr) << endl;

    myset.insert("yellow");

    vector<string> vet = { "purple", "pink" };
    myset.insert(vet.begin(), vet.end());

    // Hash table specific APIs;
    cout <<  "load factor: " << myset.load_factor() << endl;    // load_factor: ratio between the total number of elements and the total number of buckets
    string x = "read";
    cout << x << " is in bucket #" << myset.bucket(x) << endl;
    cout << "Total bucket #" << myset.bucket_count() << endl;


    return 0;
}
