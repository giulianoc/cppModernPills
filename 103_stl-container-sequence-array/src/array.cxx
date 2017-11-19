#include <iostream>
#include <array>

using namespace std;

int main()
{
    // array is a very thin layer around the native array
    // Two limitations:
    //  - the size cannot be changed
    //  - two array of integer may have different typey. For example if we have a function taking an array of 3 integer as parameter,
    //      it cannot receive an array of 4 integer (because it's a different type)

    array<int, 3> a = {3, 4, 5};
    array<int, 4> b = {3, 4, 5};
    array<int, 3> c = {3, 4, 5};

    auto itr = a.begin();
    a.size();
    a.swap(c);  // we cannot pass b array because it is a different type


    return 0;
}
