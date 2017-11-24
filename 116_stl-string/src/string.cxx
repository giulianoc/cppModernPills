#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    // Constructors
    string s1("Hello");
    string s2("Hello", 3);     // Hel (3: size)
    string s3(s1);             // Copy constructors
    string s3_1(s1, 2);        // llo   (2: start)
    string s4(s1, 2, 2);        // ll (2: start, 2: size)
    string s5(5, 'a');          // aaaaa
    string s6({'a', 'b', 'c'}); // abc (initializer list)

    // Size
    s1 = "Goodbye";
    s1.size(); s1.length();       // synonymous, both return 7
    s1.capacity();              // size of storage space currently allocated to s1 (it must be bigger than size)
    s1.reserve(100);            // allocate 100 chars for the string (change the capacity)
    s1.reserve(5);              // since the string is "Goodbye", size will be 7, even capacity will be 7
    s1.shrink_to_fit();         // shrink the capacity to hold the content

    s1.resize(9);               // Goodbye\0\0
    s1.resize(12, 'x');         // Goodbye\0\0xxx
    s1.resize(3);               // Goo

    // Single element access
    s1 = "Goodbye";
    s1[2];              // 'o' (reference to the char)
    s1[2] = 'x';        // Goxdbye
    s1.at(2) = 'y';     // Goydbye
    s1.at(20);          // throw an exception of out of range
    s1[20];             // no exception, undefined behavior

    // next API are just to be consistent with other containers
    // and like vector, string doesn't have push_front() and pop_front() because are not efficient
    s1.front();         // reference to 'G'
    s1.back();          // reference to 'e'
    s1.push_back('z');
    s1.pop_back();
    s1.begin();
    s1.end();

    string s7 (s1.begin(), s1.begin() + 3);     // Goo

    // ranged access
    s2 = "Dragon Land";
    s1.assign(s2);
    s1.assign(s2, 2, 4);    // agon when the first parameter is a string, 2 is start and 4 is size
    s1.assign("Wisdom");
    s1.assign("Wisdom", 3); // Wis  when the first parameter is a cstring, 3 is size
    s1.assign(3, 'x');      // xxx
    s1.assign({'a', 'b', 'c'}); // abc  initializer list

    // append, insert and replace has similar syntax to assign
    s1.append(" def");      // abc def
    s1.insert(2, "montain", 4); // abmontc def
    s1.replace(2, 5, s2, 3, 3); // abgon def   2: start, 5: size, 3: start, 3: size

    s1.erase(1, 4);             // a def
    s2.substr(2, 4);            // agon

    s1 = "abc";
    s1.c_str();                 // "abc\0"
    s1.data();                  // "abc\0"

    s1.swap(s2);

    s1 = "abcdefg";
    char buf[20];
    size_t len = s1.copy(buf, 3);   // buf: "abc" without \0, len = 3
    len = s1.copy(buf, 4, 2);       // buf: "cdef", len = 4

    s1 = "if a job was worth doing, it's worth doing well";
    size_t found = s1.find("doing");    // found: 17
    found = s1.find("doing", 20);       // found: 35, 20: start
    found = s1.find("doing well", 0);   // found: 35
    found = s1.find("doing well", 0, 5);   // found: 17, 0: start, 5: looking 5 chars ("doing")
    found = s1.find_first_of("doing");      // found: 6, looking for one char (in our case '0' is found first)
    found = s1.find_first_of("doing", 10);  // found: 12, 10: start
    found = s1.find_first_of("doing", 10, 1);  // found: 17, 10: start, only the first chat ('d')
    found = s1.find_first_not_of("doing");  // found: 17, 10: start, only the first chat ('d')

    found = s1.find_last_of("doing");  // found: 0
    found = s1.find_last_not_of("doing");  // found: 44


    s1.compare(s2);     // positive if s1 > s2; negative if s1 < s2; zero is s1 == s2
    s1.compare(3, 2, s2);   // 3: start, 2: size

    string ss = s1 + s2;

    cout << s1 << endl; // output
    cin >> s1;         // input
    getline(cin, s1);   // input as the previous one, delimiter: \n
    getline(cin, s1, ';');  // input until it see ';', delimiter: ';'

    // convert a number into a string
    s1 = to_string(8);
    s1 = to_string(2.3e7);   // 23000000.000000
    s1 = to_string(0xa4);    // 164
    s1 = to_string(034);     // 28

    // convert a string into a number
    s1 = "190";
    int i = stoi(s1);

    s1 = "190 monkeys";
    size_t pos;
    i = stoi(s1, &pos); // i = 190, pos will be the index of char where stoi has stopped to parsing the number, pos: 3

    s1 = "a monkeys";
    i = stoi(s1, &pos); // exception of invalid_argument
    i = stoi(s1, &pos, 16);     // 16: exedecimal, i = 10

    // stol, stod, stof, ...


    s1 = "Variety is the spice of life";

    int num = count(s1.begin(), s1.end(), 'e');     // num: 4
    num = count_if(s1.begin(), s1.end(), [](char c){return ( c <= 'e' && c >= 'a');});     // num: 6

    s1 = "Goodness is better than beauty";
    string::iterator itr = search_n(s1.begin(), s1.begin() + 20, 2, 's');   // itr --> the first 's', search 2 consecutive 's' in the first 20  chars
    s1.erase(itr, itr + 5);     // "ss is" would be removed
    s1.insert(itr, 3, 's');
    s1.replace(itr, itr + 3, 3, 'y');   // replace 3 chars starting from itr with 3 'y', replace substring

    replace(s1.begin(), s1.end(), 'e', ' ');    // replace 'e' with ' ', it replace characters
    transform(s1.begin(), s1.end(), s2.begin(),
              [](char c){
                if (c < 'n')
                    return 'a';
                else
                    return 'z';
            });

    s1 = "abcdefg";
    rotate(s1.begin(), s1.begin() + 3, s1.end());   // "defgabc" s1.begin() + 3 becomes the first char

    u16string s8;   // string of char16_t (16 bits chars)
    u32string s9;   // string of char32_t (32 bits chars)
    wstring s10;   // string of wchar_t (wide char)
    // to_wstring();



    return 0;

}
