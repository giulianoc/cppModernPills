#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	string str = "123@gmail.com; 456@hotmail.com;; 789@catrasoft.com";

    regex e("([[:w:]]+)@([[:w:]]+)\.com");

 	// Regex iterator
 	{
        sregex_iterator pos(str.cbegin(), str.cend(), e);
        sregex_iterator end;    // default constructor defines past-the-end iterator

        for (; pos!=end; pos++)
        {
            cout << "Matched: " + pos->str(0) << endl;
            cout << "User name: " + pos->str(1) << endl;
            cout << "Domain: " + pos->str(2) << endl;
            cout << endl;
        }
 	}

 	cout << "==================================" << endl << endl;

 	// Regex token iterator
 	{
 	    {
            sregex_token_iterator posToken(str.cbegin(), str.cend(), e, 0); // 0: entire match of the regular expression will be extracted
            sregex_token_iterator endToken;    // default constructor defines past-the-end iterator

            for (; posToken!=endToken; posToken++)
            {
                cout << "Matched: " + posToken->str() << endl;
                cout << endl;
            }
 	    }

        cout << "==================================" << endl << endl;

        {
            sregex_token_iterator posToken(str.cbegin(), str.cend(), e, 1); // 1: first submatch of the regular expression will be extracted
            sregex_token_iterator endToken;    // default constructor defines past-the-end iterator

            for (; posToken!=endToken; posToken++)
            {
                cout << "Matched: " + posToken->str() << endl;
                cout << endl;
            }
        }

        cout << "==================================" << endl << endl;

        {
            sregex_token_iterator posToken(str.cbegin(), str.cend(), e, 2); // 1: second submatch of the regular expression will be extracted
            sregex_token_iterator endToken;    // default constructor defines past-the-end iterator

            for (; posToken!=endToken; posToken++)
            {
                cout << "Matched: " + posToken->str() << endl;
                cout << endl;
            }
        }

        cout << "==================================" << endl << endl;

        {
            sregex_token_iterator posToken(str.cbegin(), str.cend(), e, -1);    // -1: all the part of the string that is not matched with the regular expression will be extracted
            sregex_token_iterator endToken;    // default constructor defines past-the-end iterator

            for (; posToken!=endToken; posToken++)
            {
                cout << "Matched: " + posToken->str() << endl;
                cout << endl;
            }
        }
 	}

    cout << "==================================" << endl << endl;

 	// regex_replace
 	{
 	    // replace the entire matched string (email) with "$1 is on $2"
 	    // $1 is substituted with the first submatch
        // $2 is substituted with the second submatch
        cout << regex_replace(str, e, "$1 is on $2") << endl;

        cout << "==================================" << endl << endl;

        // format_no_copy: what it is not matched is not copied
        cout << regex_replace(str, e, "$1 is on $2", regex_constants::format_no_copy) << endl;

        cout << "==================================" << endl << endl;

        // format_first_only: only the first match is considered a match
        cout << regex_replace(str, e, "$1 is on $2", regex_constants::format_no_copy | regex_constants::format_first_only) << endl;
 	}

    cout << "==================================" << endl << endl;
}
