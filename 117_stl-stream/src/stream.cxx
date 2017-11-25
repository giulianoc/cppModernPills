#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Dog {
    int age_;
    string name_;
};

ostream& operator << (ostream& sm, const Dog& d)
{
        sm << "My name is " << d.name_ << " and my age is " << d.age_ << endl;

        return sm;
}

istream& operator >>(istream& sm, Dog& d)
{
    sm >> d.age_;
    sm >> d.name_;

    return sm;
}

int main()
{
    cout << "Hello" << endl;
    // cout: global object of ostream (typedef of basic_ostream<char> ostream)
    // <<: ostream& ostream::operator << (string v)
    // endl: \n + flush

    // Stream? Serial IO Interface to external devices (file, stdin/stdout, network, ...).
    // Serial as opposite to Random access. With Serial IO it is not possible to do cout [3]

    {
        ofstream of("mylog.txt");   // create a new file for write if it does not exist
        of << "Expirience is the mother os widsom" << endl;
        of << 234 << endl;
        of << 2.3 << endl;
        // of << bitset<8>(14) << endl;    // 00001110
        // of << complex<int>(2, 3) << endl;   // (2,3)

        // file is closed when of of is destroyed (typical RAII technique)
    }

    // IO Operation:
    //  - formatting the data (stream module)
    //  - communicating the data with external device (stream buffer module, it is a module inside the stream module)
    //  We have two different modules to format and communicate data, formatting data module is independently
    //  by the communicating module. That allow to reuse the formatting module independently be the channel used
    //  to communicate
    cout << 34;     // cout is responsible to convert 34 in an appropriate format and then delegate the job of communicating data to his internal stream buffer module

    {
        // ofstream of("mylog.txt");   // open the file for write and it clear the content of the file
        ofstream of("mylog.txt", ofstream::app);   // open the file for write and move the output pointer at the end of the file

        of << "Honesty is the best policy." << endl;
    }

    {
        ofstream of("mylog.txt", ofstream::in  | ofstream::out);   // open the file for write having the possibility to move the pointer inside the file
        of.seekp(10, ios::beg);    // move the output pointer 10 chars after begin
        of << "12345";                  // overwrite 5 chars
        of.seekp(-5, ios::end);
        of << "Nothing ventured, nothing gained." << endl;
        of.seekp(-5, ios::cur);
    }

    {
        ifstream inf("mylog.txt");
        int i;
        inf >> i;   // read one word, in case the first word is not an integer, this operation will fail

        // Error status: goodbit, badbit, failbit, eofbit
        inf.good(); // everything is ok, goodbit is 1
        inf.bad();  // Non-recoverable error, badbit is 1
        inf.fail(); // failed stream operation, failbit is 1, badbit is 1
        inf.eof();  // end of file eofbit is 1

        // if an error happened and we need to clear the error status and go ahead
        inf.clear();                // equivalent to inf.clear(ios;goodbit);
        inf.clear(ios::badbit);     // sets a new value to the error flag

        inf.rdstate();              // read the current status
        inf.clear(inf.rdstate() & ~ios::failbit);  // clear only the failbit

        if (inf)    // equivalent to if (!inf.fail())
            cout << "Read successfully";

        if (inf >> i)
            cout << "Read successfully";

        // handle the errors with exceptions
        inf.exceptions(ios::badbit | ios::failbit);   // setting the exception mask
        // when badbit or failbit set to 1, exception of ios::failure will be thrown
        // when eofbit set to 1, no exception
        inf.exceptions(ios::goodbit);     // no exception would be generated
    }


    // formatting
    cout << 34 << endl;             // 34
    cout.setf(ios::oct, ios::basefield);
    cout << 34 << endl;             // 42
    cout.setf(ios::showbase);
    cout << 34 << endl;             // 042
    cout.setf(ios::hex, ios::basefield);
    cout << 34 << endl;             // 0x22
    cout.unsetf(ios::showbase);
    cout << 34 << endl;             // 22

    cout.setf(ios::dec, ios::basefield);

    cout.width(20);
    cout << 26 << endl;             //                       26
    cout.setf(ios::left, ios::adjustfield);
    cout << 26 << endl;             //26

    // Floating point value
    cout.setf(ios::scientific, ios::floatfield);
    cout << 340.1 << endl;          // 3.401000e+002
    cout.setf(ios::fixed, ios::floatfield);
    cout << 340.1 << endl;          // 340.100000
    cout.precision(3);
    cout << 340.1 << endl;          // 340.100

    int i;
    cin.setf(ios::hex, ios::basefield);
    cin >> i;   // Entering 12
    // i is 18

    ios::fmtflags f = cout.flags();
    cout.flags(ios::oct | ios::showbase);


    // member functions for unformatted IO (raw text)
    // input
    ifstream inf("mylog.txt");
    char buf[80];
    inf.get(buf, 80);       // read up to 80 chars and save into buf
    inf.getline(buf, 80);   // read up to 80 chars or until \n
    inf.read(buf, 20);      // read 20 chars
    inf.ignore(3);          // ignore 3 chars in the stream
    inf.peek();             // return the char on top of the stream
    inf.unget();            // return a char back to a stream
    inf.get();              // read one char
    inf.gcount();           // return the number of chars being read by last unformatted read

    // output
    ofstream of("mylog.txt");
    of.put('c');
    of.write(buf, 6);   // write first 6 chars of buf
    of.flush();


    // Manipulator
    /*
        endl is a manipulator. It is a function, endl and << are defined like this:
        ostream& endl(ostream& sm) { sm.put('\n'); sm.flush(); return sm; }
        ostream& ostream::operator << (ostream& (*func)(ostream&)) { return (*func)(*this); }
    */
    cout << "Hello" << endl;
    cout << ends;               // '\0'
    cout << flush;
    cin >> ws;                  //  read and discard white spaces

    cout << setw(8) << left << setfill('_') << 99  << endl; //99______
    cout << hex << showbase << 14;                          // 0xe

    // more manipulator in documentation: http://www.cplusplus.com/reference/ios/ and http://www.cplusplus.com/reference/iomanip/


    cout << 34;     // cout is responsible to convert 34 in an appropriate format and then delegate the job of communicating data to his internal stream buffer module
    streambuf* pbuf = cout.rdbuf();   // return a pointer to his stream buffer internal module
    ostream myCout(pbuf);               // created another ostream having the same streambuf as cout
    myCout << 34;                       // 34 to stdout
    myCout.setf(ios::showpos);
    myCout.width(20);
    myCout << 12 << endl;   //            +12
    cout << 12 << endl;     //12
    // this is useful when it is needed to change temporary the format to the standard out without changing cout

    // redirecting
    {
        ofstream of("mylog.txt");
        streambuf* origBuf = cout.rdbuf();
        cout.rdbuf(of.rdbuf());
        cout << "Hello" << endl;    // writes in mylog.txt
        cout.rdbuf(origBuf);
        cout << "Goodbye" << endl;  // writes to standard out
    }

    // String stream: stream without IO Operations. It can write data into a string and read data from a string. This is to reuse all the formatting functions of a Stream into a string
    stringstream ss;
    ss << 89 << " Hex: " << hex << 89 << " Oct: " << oct << 89;   // write to ss
    cout << ss.str() << endl;   // 89 Hex: 59 Oct: 131

    int a, b, c;
    string s1;
    ss >> hex >> a; // read the first word and parse as a hexadecimal. Input works token by token separated by spaces, tabs and newlines
        // The first token is 89, read as hexadecimal, so a==137
    ss >> s1;       // s1 == "Hex:"
    ss >> dec >> b; // b == 59
    ss.ignore(6);
    ss >> oct >> c; // c == 89


    // Enable Streaming for a custom class
    Dog d{12, "Bob"};   // Universal initialization
    cout << d;

    cin >> d;
    cout << d;


    return 0;
}
