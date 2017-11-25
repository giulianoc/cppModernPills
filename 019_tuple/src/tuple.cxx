#include <iostream>
#include <tuple>
#include <functional>   // because of ref
#include <map>

using namespace std;

ostream& operator<< (ostream& os, pair<int,string>& p)
{
    cout << p.first << " " << p.second << endl;

    return os;
}

int main ()
{
    pair<int,string> p = make_pair(23, "hello");
    cout << p;

    tuple<int, string, char> t(32, "Penny wise", 'a');
    cout << get<0>(t) << endl;
    cout << get<1>(t) << endl;
    cout << get<2>(t) << endl;

    get<1>(t) = "Pound foolish";
    string& s = get<1>(t);
    s = "Patience is virtue";   // changes t

    // get<3>(t);   this would not compile: out of range
    // index for the get function has to be a compile time constant
    int i = 1;
    // get<i>(t); this would not compile because i is not a constant

    tuple<int, string, char> t2;    // default constructor for each element
    t2 = tuple<int, string, char>(12, "Curiosity kills the cat", 'd');
    t2 = make_tuple(12, "Curiosity kills the cat", 'd');

    if (t > t2) // lexicographical comparison
    {
        cout << "t is larger than t2" << endl;  // 32 is larger than 12
        t = t2;             // member by menber copying
    }

    // Tuple can store references
    string st = "In for a penny";
    tuple<string&> t3(st);
    t3 = make_tuple(ref(st));
    // get<0>(t) = "In for a pound";       // st also contains "In for a pound", compiler generate an error unless -fpermissive option is used

    int x;
    string y;
    char z;
    tie(x, y, z) = t2;          // result will be x: 12, y: "Curiosity kills the cat", z: 'd'
    tie(x, ignore, z) = t2;

    auto t4 = tuple_cat(t2, t3);        // t4 is a tuple<int, string, char, string>

    // type traits
    cout << tuple_size<decltype(t4)>::value << endl;    // 4
    tuple_element<1, decltype(t4)>::type d;             // d is a string

    // tutple vs struct
    // Both can be used to save groups of data but
    //  - tuple is a convenient utility as a one-time only structure, that will save us to build a dedicated struct to save the data

    // comparison of tuples
    tuple<int, int, int> time1, time2;  // hours, minutes and seconds
    if (time1 > time2)
        cout << "time1 is a later time" << endl;

    // Multi index map
    map<tuple<int, char, float>, string> m;
    m[make_tuple(2, 'a', 2.3)] = "Faith will move montains";

    // tuple used to rotate the data
    int a, b, c;
    tie(b, c, a) = make_tuple(a, b, c);

}
