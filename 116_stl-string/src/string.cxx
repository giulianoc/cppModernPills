#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

string& ltrim(string& s)
{
	auto it = find_if(s.begin(), s.end(),
		[](char c)
		{
			return !isspace<char>(c, locale::classic());
		});
	s.erase(s.begin(), it);

	return s;
}

string& rtrim(string& s)
{
	auto it = find_if(s.rbegin(), s.rend(),
		[](char c)
		{
			return !isspace<char>(c, locale::classic());
		});
	s.erase(it.base(), s.end());

	return s;
}

string& trim(string& s)
{
	return ltrim(rtrim(s));
}

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
    // s1.at(20);          // throw an exception of out of range
    // s1[20];             // no exception, undefined behavior

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
    
    // replace a substring in a string with another substring
    cout << endl;
    cout << "Replace." << endl;
    string test = "{	\"Type\": \"Process\",	\"Label\": \"1\",	\"Variables\": {  		\"Title\": \"My Title of the content\"	},	\"Task\": {		\"Label\": \"nome univoco del task all'interno del processo\",		\"Type\": \"ContentIngestion\",		\"Parameters\": {		\"SourceURL\": \"http://techslides.com/demos/sample-videos/small.mp4\",			\"SourceFileName\": \"123456.mp4\",			\"ContentType\": \"video\",			\"userData\": { \"MyData\": \"this is my data\" },			\"Title\": \"_Title_\"		}	}}";
    cout << "Test before replace: " << test << endl;
    string variableToBeSearched = string("Type");
    string value = "k l m g h r s y u o a w e r";
	cout << "replace " << variableToBeSearched << " with " << value << endl;
    string test2 = regex_replace(test, regex(variableToBeSearched), value);
    cout << "Test after replace: " << test << endl;
    cout << "Test2 after replace: " << test2 << endl;

    s1.erase(1, 4);             // a def
    s2.substr(2, 4);            // return: agon, s2 remain as is

    s1 = "abc";
    s1.c_str();                 // "abc\0"
    s1.data();                  // "abc\0"

    s1.swap(s2);

    s1 = "abcdefg";
    char buf[20];
    size_t len = s1.copy(buf, 3);   // buf: "abc" without \0, len = 3
    len = s1.copy(buf, 4, 2);       // buf: "cdef", len = 4

    s1 = "if a job was worth doing, it's worth doing well";
    size_t found = s1.find("doing");    // look for the entire string "doing", found: 17,        string::npos in case it is not found
    found = s1.find("doing", 20);       // found: 35, 20: start
    found = s1.find("doing well", 0);   // found: 35
    found = s1.find("doing well", 0, 5);   // found: 17, 0: start, 5: looking 5 chars ("doing")
    found = s1.find_first_of("doing");      // found: 6, looking for one char (in our case '0' is found first)
    found = s1.find_first_of("doing", 10);  // found: 12, 10: start
    found = s1.find_first_of("doing", 10, 1);  // found: 17, 10: start, only the first chat ('d')
    found = s1.find_first_not_of("doing");  // found: 17, 10: start, only the first chat ('d')

    found = s1.find_last_of("doing");  // found: 0 (Searches the string for the last character that matches any of the characters specified in its arguments)
    found = s1.find_last_not_of("doing");  // found: 44


    s1.compare(s2);     // positive if s1 > s2; negative if s1 < s2; zero is s1 == s2
    s1.compare(3, 2, s2);   // 3: start, 2: size
    
    // next is end with
    string suffix(".mp4");
    if (s1.size() >= suffix.size() && 0 == s1.compare(s1.size()-suffix.size(), suffix.size(), suffix)) ;
 
    // next is start with
    string prefix ("if a job");
    if (s1.size() >= prefix.size() && 0 == s1.compare(0, prefix.size(), prefix)) ;
    
    // compare case insensitive
    {
        string a ("abcd");
        string b ("abcde");
        bool isEqual = a.length() != b.length() ? false : 
            equal(a.begin(), a.end(), b.begin(), [](int c1, int c2){ return toupper(c1) == toupper(c2); });
        
        cout << "isEqual: " << isEqual << endl;
        
        // a simpler API would be: 
        //  int strcasecmp(const char *string1, const char *string2);Copy
    }

    string ss = s1 + s2;

    cout << s1 << endl; // output
    cout << "write an input string (\\n to terminate): ";
    cin >> s1;         // input
    cout << "another one (\\n to terminate): ";
    getline(cin, s1);   // input as the previous one, delimiter: \n
    cout << "another one (; to terminate): ";
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
    // i = stoi(s1, &pos); // exception of invalid_argument
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

    // replace the first substring with another substring. The initial buffer is modified
    {
		cout << endl;
        string strbase = "abc def ghi lmn";
        cout << "current strbase: " << strbase << endl;
        string strToBeReplaced = "def";
        string strToReplace = "123456";
        cout << "replace " << strToBeReplaced << " with " << strToReplace << endl;
        if (strbase.find(strToBeReplaced) != string::npos)
            strbase.replace(strbase.find(strToBeReplaced),strToBeReplaced.length(),strToReplace);
        
        cout << "new strbase: " << strbase << endl;
    }
    replace(s1.begin(), s1.end(), 'e', ' ');    // replace 'e' with ' ', it replace characters

    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    transform(s1.begin(), s1.end(), s2.begin(),
              [](char c){
                if (c < 'n')
                    return 'a';
                else
                    return 'z';
            });
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    s1 = "abcdefg";
    rotate(s1.begin(), s1.begin() + 3, s1.end());   // "defgabc" s1.begin() + 3 becomes the first char

	// trim
	{
		cout << "trim demo:" << endl;
		string s("  123   ");
		cout << "s: " << s << ", ltrim(s): '" << ltrim(s) << "'" << endl;
		s = "  123   ";
		cout << "s: " << s << ", rtrim(s): '" << rtrim(s) << "'" << endl;
		s = "  123   ";
		cout << "s: " << s << ", trim(s): '" << trim(s) << "'" << endl;

		s = "  123   ";
		trim(s);
		cout << "s: '" << s << "'" << endl;
	}

    {
        // given a string, convert it to lowercase and count the length of the non-empty words of the string
        s1 = "Hello       World";

        cout << "Lowercase on a different string. s1: " << s1 << ", s2: " << s2 << endl;
        s2.resize(s1.size());
        transform(s1.begin(), s1.end(), s2.begin(), [](unsigned char c){return tolower(c); } );
        cout << "result. s1: " << s1 << ", s2: " << s2 << endl;

        cout << "Lowercase on the same string: " << s1 << endl;
        transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){return tolower(c); } );
        cout << "result: " << s1 << endl;

        cout << "Splitting in words (option 1): " << s1;    // drawback. it can’t split on anything else than spaces, which can be an issue, like for parsing a CSV
        istringstream iss(s1);
        vector<string> words;
        copy(
            istream_iterator<std::string>(iss),
            istream_iterator<std::string>(),
            back_inserter(words)
        );
        cout << "result:" << endl;
        for (string s: words)
            cout << s.length() << endl;

        cout << "Splitting in words (option 2): " << s1;
        words.clear();
        stringstream ss(s1);
        string token;
        char delim = ' ';
        while (getline(ss, token, delim)) 
        {
            if (!token.empty())
                words.push_back(token);
        }
        
        cout << "result:" << endl;
        for (string s: words)
            cout << s.length() << endl;
    }
    
    u16string s8;   // string of char16_t (16 bits chars)
    u32string s9;   // string of char32_t (32 bits chars)
    wstring s10;   // string of wchar_t (wide char)
    // to_wstring();



    return 0;

}
