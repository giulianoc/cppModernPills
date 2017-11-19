

#include <iostream>

using namespace std;

int operator "" _bin(const char *str, size_t l) {
	int ret = 0;
	for (auto i = 0; i < l; i++)
	{
		ret = ret << 1;
		if (str[i] == '1')
			ret += 1;
	}
	
	return ret;
}
// constexpr make the calculation made at compile time
constexpr long double operator "" _cm(long double x) { return x * 10; }
constexpr long double operator "" _m(long double x) { return x * 1000; }
constexpr long double operator "" _mm(long double x) { return x; }

// Restriction on input parameters:
//	- char const*
//	- unsigned long long
//	- long double
//	- char const*, std::size_t
//	- wchar_t const*, std::size_t
//	- char16_t const*, std::size_t
//	- char32_t const*, std::size_t
// Return value can be of any type

int main(int argc, char **argv)
{

		long double height = 3.4_cm;
		
		cout << height << endl;
		cout << (height + 13.0_m) << endl;
		cout << (130.0_mm / 13.0_m) << endl;
		cout << (130.0_mm / 0.0_m) << endl;

		cout << "110"_bin << endl;
		cout << "1100110"_bin << endl;
		cout << "110100010001001110001"_bin << endl;
		
		return 0;
}

