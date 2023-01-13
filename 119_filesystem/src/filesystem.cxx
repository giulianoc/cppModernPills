#include <string>  
#include <iostream>  
#include <sstream>  
#include <chrono>  
#include <filesystem>  
#include <fstream>  

using namespace std;

std::uintmax_t computeFileSize(const filesystem::path& pathToCheck)
{
	if (filesystem::exists(pathToCheck) && filesystem::is_regular_file(pathToCheck))
	{
		auto err = std::error_code{};
		auto filesize = filesystem::file_size(pathToCheck, err);
		if (filesize != static_cast<uintmax_t>(-1))
			return filesize;
	}

	return static_cast<uintmax_t>(-1);
}

// example adapted from https://docs.microsoft.com/pl-pl/cpp/standard-library/file-system-navigation
void displayPathInfo(const filesystem::path& pathToShow)
{
	int i = 0;	
	cout << "Displaying path info for: " << pathToShow.string() << "\n";
	for (const auto& part : pathToShow)
	{
		cout << "path part: " << i++ << " = " << part << "\n";
	}

	cout << "exists() = " << filesystem::exists(pathToShow) << "\n"
		<< "root_name() = " << pathToShow.root_name() << "\n"
		<< "root_path() = " << pathToShow.root_path() << "\n"
		<< "relative_path() = " << pathToShow.relative_path() << "\n"
		<< "parent_path() = " << pathToShow.parent_path() << "\n"
		<< "filename() = " << pathToShow.filename() << "\n"
		<< "stem() = " << pathToShow.stem() << "\n"
		<< "extension() = " << pathToShow.extension() << "\n"
	;

	try
	{
		cout << "canonical() = " << filesystem::canonical(pathToShow) << "\n";
	}
	catch (filesystem::filesystem_error err)
	{
		cout << "exception: " << err.what() << "\n";
	}
}

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
              + system_clock::now());
    return system_clock::to_time_t(sctp);
}

void displayFileInfo(
	const filesystem::directory_entry& entry,
	filesystem::path& filename)
{
	filesystem::file_time_type fileTime = filesystem::last_write_time(entry);
	time_t cftime = to_time_t(fileTime);

	cout << "filename: " << filename << ", " 
		<< computeFileSize(entry) 
		<< ", time: " << asctime(localtime(&cftime))
	;
}

void displayDirectoryTreeImp(const filesystem::path& pathToShow, int level)
{
	if (filesystem::exists(pathToShow) && filesystem::is_directory(pathToShow))
	{
		for (const auto& directoryEntry : filesystem::directory_iterator(pathToShow))
		{
			auto filename = directoryEntry.path().filename();
			if (filesystem::is_directory(directoryEntry.status()))
			{
				cout << "[+] " << filename << "\n";
				displayDirectoryTreeImp(directoryEntry, level + 1);
				cout << "\n";
			}
			else if (filesystem::is_regular_file(directoryEntry.status()))
				displayFileInfo(directoryEntry, filename);
			else
				cout << " [?]" << filename << "\n";
		}
	}
}

void readFile(const filesystem::path& path)
{
	ifstream f(path, ios::in | ios::binary);

	// see stream.cxx
}

int main(int argc, char* argv[])
{
	try
	{
		const filesystem::path pathToShow{ argc >= 2 ? argv[1] : filesystem::current_path() };

		displayPathInfo(pathToShow);

		cout << "path concat/append:\n";
		filesystem::path p1("C:\\temp");
		p1 /= "user";
		p1 /= "data";
		cout << p1 << "\n";

		filesystem::path p2("C:\\temp\\");
		p2 += "user";
		p2 += "data";
		cout << p2 << "\n";

		displayDirectoryTreeImp(pathToShow, 0);
	}
	catch(filesystem::filesystem_error& e)
	{
		cerr << "exception: " << e.what() << endl;
	}

	return 0;
}

