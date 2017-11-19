#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	// Regular expression: specific pattern that provides concise and flexible means
	//	to "match" strings of text

	string str;
	while (true)
	{
		cin >> str;

        // Next I want to extract a portion of the email address, for example the username and domain
        // First I have to define the groups (submatch) to define username e domain name
        {
            smatch m;   // typedef std:match_result<string>

            regex e("([[:w:]]+)@([[:w:]]+)\.com");

            bool match = regex_search(str, m, e);

            // m is where the result is saved
            // we will have three results: the entire match, the first submatch, the second submatch
            // giving the following input: <email>user@gmail.com<end>
            // m.prefix(): everything is in front of the matched string (<email> in the previous example)
            // m.suffix(): everything is after the matched string (<end> in the previous example)

            cout << "m.size() " << m.size() << endl;
            for (int n = 0; n < m.size(); n++)
            {
                cout << "m[" << n << "]: str()=" << m[n].str() << endl; // m.str(n) and *(m.begin()+n) provides same result
            }
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
        }
	}

}
