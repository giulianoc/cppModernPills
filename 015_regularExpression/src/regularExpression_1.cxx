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

		regex e("abc");
		// regex e("abc", regex_constants::icase);

		// ^        only abc at the beginning of the string
		// regex e("^abc");

		// $        only abc at the end of the string
		// regex e("abc$");

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

		// []		any character NOT inside the square brackets (any chars except 'c' or 'd')
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

		// ()		define a group. So it matches for example: abcdeeeedeeeeeab
		// regex e("(ab)c(de+)\\2\\1");

		// email address ending with .com
		// [[:w:]] ---> word character: digit, number or undescore
		// regex e("[[:w:]]+@[[:w:]]+\.com");

		// [[:alnum:]]  alpha-numerical character   equivalemt to isalnum
		// [[:alpha:]]  alphabetic character   equivalemt to isalpha
		// [[:blank:]]  blank character   matches only space and tab
		// [[:cntrl:]]  control character   equivalemt to iscntrl
		// [[:digit:]]  decimal digit character   equivalemt to isdigit
		// [[:graph:]]  character with graphical representation   equivalemt to isgraph
		// [[:lower:]]  lowercase letter   equivalemt to islower
		// [[:print:]]  printable character   equivalemt to isprint
		// [[:punct:]]  punctuation mark character   equivalemt to ispunct
		// [[:space:]]  whitespace character   equivalemt to isspace
		// [[:upper:]]  uppercase letter   equivalemt to isupper
		// [[:xdigit:]]  hexadecimal digit character   equivalemt to isxdigit
		// [[:d:]]  decimal digit character   equivalemt to isdigit
		// [[:w:]]  word character   equivalemt to isalnum
		// [[:s:]]  whitespace character   equivalemt to isspace

        // Regular expression grammars: ECMAScript (default), basic, extended, awk, grep, egrep
        // here follows how to set the grep regular expression
        // Using the grep regular expression, + does not mean one or more preceding character but just the '+' character
		// regex e("abc.+", regex_constants::grep);

		// to match a string like this
		// str = "2021-12-22 23:18:54 SSC Bari restarted because of 'segment";
		// regex e("^[[:digit:]]{4}-[[:digit:]]{2}-[[:digit:]]{2}[[:space:]][[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2}.*");


		// check if the entire str string matches
		bool match = regex_match(str, e);

		// check if a substring of str matches
		// bool match = regex_search(str, e);

		cout << (match ? "Matched" : "Not matched") << endl << endl;
	}

}
