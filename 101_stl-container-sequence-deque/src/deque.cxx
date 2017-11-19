#include <iostream>
#include <deque>

using namespace std;

int main()
{
    // deque and vector have a very similar interface.
    // The biggest difference between them is that:
    //  - vector can only grow at the end of the vector,
    //  - deque can grow both at the end and at the beginning
    // The underline Deque implementation does not provide contiguous data

    // Properties of the Deque:
    //  1. fast insert and remove at the beginning and the end: O(1)
    //  2. slow insert-remove in the middle: O(n)
    //  3. slow search: O(n)

    deque<int> deq = { 4, 6, 7 };
    deq.push_front(2);  // deq: { 2, 4, 6, 7 }
    deq.push_back(3);   // deq: { 2, 4, 5, 7, 3 }

    // random access
    cout << deq[1] << endl;     // 4

    return 0;
}
