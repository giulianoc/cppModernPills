
#include <iostream>
#include <forward_list>
#include <unordered_map>

using namespace std;


template <typename T>
pair<T, int> getMostFrequent(forward_list<T>& flist)
{
	unordered_map<T, int> mostFrequents;
	
	for (auto& value: flist)
		++mostFrequents[value];		
	
	pair<T, int> mostFrequent;
	
	for (auto& itemMostFrequent: mostFrequents)
	{
		if (itemMostFrequent.second > mostFrequent.second)
		{
			mostFrequent.first = itemMostFrequent.first;
			mostFrequent.second = itemMostFrequent.second;
		}
	}
	
	return mostFrequent;
}

template <typename T>
ostream& operator << (ostream& os, const pair<T, int>& p)
{
	os << p.first << " - " << p.second;

	return os;
}

int main(int argc, char **argv)
{
	forward_list<int> flist = {1, 2, 3, 4, 5, 6, 7, 1};
	
	pair<int, int> mostFrequent = getMostFrequent(flist);
	
	cout << mostFrequent << endl;
	
	
	return 0;
}

