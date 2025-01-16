#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  // map values are always sorted according to a key (not according to a value
  // as for set). So every node of a map is a pair: key-value Map has the same
  // interface as a set except that each element is a pair of key-value map does
  // not have elements with duplicate keys keys cannot be modified, iterator is
  // a constant iterator it has the [] operator, important for the associative
  // array (see dedicated pill) Properties of a set are still valid for a map

  // set, multiset, map and multimap are 'associative' container
  // the 'associative' container comes from the map where a value is associated
  // with a key. The set and multiset can be thought as a kind of map and
  // multimap where key is the same as the value.

  map<char, int> mymap;
  mymap.insert(pair<char, int>('a', 100));
  mymap.insert(make_pair('z', 200));

  map<char, int>::iterator it = mymap.begin();
  mymap.insert(it, pair<char, int>('b', 300)); // it is an hint

  it = mymap.find('z');

  // per rimuovere un elemento della mappa
  mymap.erase(it);

  // key of the elements cannot be modified, it is a constant iterator
  // (*it).first = 'd';       compiler generates an error

  for (it = mymap.begin(); it != mymap.end(); it++)
    cout << (*it).first << " ==> " << (*it).second << endl;

  cout << endl;

  for (pair<char, int> keyValue : mymap)
    cout << keyValue.first << " ==> " << keyValue.second << endl;

  // Per avere la lista delle keys di una mappa è possibile
  // 1. utilizzare il loop e mettere keyValue.first ad es in un vettore oppure
  // 2. usare transform (vedi sotto)
  vector<char> keys;
  transform(mymap.begin(), mymap.end(), back_inserter(keys),
            [](const pair<int, string> &pair) { return pair.first; });

  return 0;
}
