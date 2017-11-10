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
		
		// regex e("abc");
		// regex e("abc", regex_constants::icase);

		// .		any character except newline
		// regex e("abc.", regex_constants::icase);
		
		// ?		zero or one preceding character (that is c). So it matches: ab, abc
		// regex e("abc?");

		// *		zero or more preceding character (that is c). so it matches: ab, abc, abcc, abccc, ...
		// regex e("abc*");

		// +		one or more preceding character (that is c). so it matches: abc, abcc, abccc, ...
		// regex e("abc+");

		// []		any character inside the square brackets
		// regex e("ab[cd]*");

		// []		any character NOT inside the square brackets
		// regex e("ab[^cd]*");

		// {3}		exactly 3 appearence of the preceding character
		// regex e("ab[cd]{3}");

		// {3,}		exactly 3 or more appearence of the preceding character
		// regex e("ab[cd]{3,}");

		// {3,5}		3 or 4 or 5 appearence of the preceding character
		// regex e("ab[cd]{3,5}");

		// |		OR ----> abc OR de[\]fg]	To include ] as possible match, \ is used
		// regex e("abc|de[\]fg]");

		// ()		define a group. \\1 is the position where we have again the group 1. So it matches for example: abcdeeeeabc
		// regex e("(abc)de+\\1");

		// ()		define a group. So it matches for example: abcdeeeedeeeeab
		// regex e("(ab)c(de+)\\2\\1");

		bool match = regex_match(str, e);
		
		cout << (match ? "Matched" : "Not matched") << endl << endl;
	}
	
}
