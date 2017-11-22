#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

class AddValue {
    int val;
public:
    AddValue() : val(0) {};
    AddValue(int i) : val(i) {};

    void operator ()(int i)
    {
        cout << "Calling functor AddValue with parameter " << i << ", AddValue is: " << (i + val) << endl;
    }

    // do not confuse it with a type conversion, i.e. string type conversion is:
    operator string () const { return "X"; }
};

class NeedCopy {
    public:
    bool operator ()(int x)
    {
        return (x > 20) || (x < 5);
    }
};

int main()
{
    // functor: function object. it extents the idea of a function by saying everything behave like a function is a function
    // benefits of a functor:
    //  1. Smart function: capabilities beyond operator (). It can remember the state
    //  2. it can have its own type

    AddValue foo;
    foo(2);

    // Functor introduces the concept of 'Parameterized function"
    AddValue(8)(3);


    // Usage of a functor
    vector<int> vec = {1, 2, 3, 4, 5};
    for_each(vec.begin(), vec.end(), AddValue(5));


    // stl provides built-in functors: less, greater, greater_equal, less_equal, not_equal_to,
    //  logical_and, logical_not, logical_or, multiplies, minus, plus, divide, modulus, negate
    int x = multiplies<int>()(3, 4);    // equivalent to x = 3 * 4;


    // assume we have to multiply myset's element by 10 and save in vec
    set<int> myset = {3, 1, 25, 7, 12};
    vector<int> vec2;
    transform(myset.begin(), myset.end(),    // source range
             back_inserter(vec2),           // back_inserter: return a special output_ iterator where the override/copy is implemented with push_back() to insert new element
             bind(multiplies<int>(), placeholders::_1, 10)  // transform takes a function taking only one parameter. So we use bind that returns the multiplies<int> function
                                                            // where the first parameter (_1) is the one coming from myset and the second parameter is 10
             );
    for (int i: vec2)
        cout << i << " ";
    cout << endl;

    // assume we have to copy everything from myset having the condition x > 20 or x < 5 to deque d
    deque<int> d;
    copy_if(myset.begin(), myset.end(),
             back_inserter(d),
             bind(logical_or<bool>(),
                  bind(greater<int>(), placeholders::_1, 20),
                  bind(less<int>(), placeholders::_1, 5)
                  )
              );
    for (int i: d)
        cout << i << " ";
    cout << endl;


    // Predicate, a functor or function that:
    //  1. returns a boolean
    //  2. does not modify data
    // For the previous sample we can use a Predicate:
    d.clear();
    copy_if(myset.begin(), myset.end(),
             back_inserter(d),
             NeedCopy());
    for (int i: d)
        cout << i << " ";
    cout << endl;

    return 0;

}
