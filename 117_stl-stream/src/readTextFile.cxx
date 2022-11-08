#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

int main (int iArgc, char *pArgv [])
{
	if (iArgc != 2)
	{
		std:: cerr << "Usage: " << pArgv [0] << " <filePathName>"
			<< std:: endl;

		return 1;
	}

	string filePathName = pArgv [1];

	ifstream segmentList;
	segmentList.open(filePathName, ifstream::in);
	if (!segmentList)
	{
		cerr << "Failed to open the file: " << filePathName << endl;

		return 1;
	}                                                                                                 

	string manifestLine;
	while(getline(segmentList, manifestLine))                                                         
	{
		cout << manifestLine << endl;
	}

    return 0;
}
