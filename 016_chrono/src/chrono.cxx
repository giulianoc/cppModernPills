#include <chrono>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    // chrono: a precision-neutral library for time and date
    //  it separates duration and time point from the clock

    // Clocks (are time providers, consisting of a starting point (“epoch”) and a tick rate):
    //  std::chrono::system_clock: current time according to the system
    //  std::chrono::steady_clock: goes at uniform rate (this is not always like the system_clock because the system clock
    //      can be modified by the user, I mean if the user move the system time 2 hours later, looking at the system_clock
    //      seems like 2 hours passed, steady_clock even in this case, say it is passed just 2 minutes for example)
    //  std::chrono::high_resolution_clock: provides smallest possible tick period. This is in case we need an high resolution for the clock

    // Time point:
    //  - represents how much time has passed since the start of the clock
    //  - You won’t be able to initialise it with the now() of a different clock because its time_point type isn’t convertible to that of the original clock
    //  - It can be added to and subtracted from other time_point instances):
    //  std::chrono::time_point<>:  represent a point of time starting from 00:00 January 1970 (UTC) - epoch of clock
    //  time_point<system_clock, milliseconds>: the elapsed time since epoch in milliseconds, according to system_clock
    //  Each clock has its own time_point definition:
    //      system_clock::time_point    -- time_point<system_clock, system_clock::duration>
    //      steady_clock::time_point    -- time_point<steady_clock, system_clock::duration>

    // Duration:
    //  - A duration is, like a time_point, just a puffed-up arithmetic type.
    //  - Unlike time_point, it’s not coupled to a specific clock type at compile time.
    //  - Along with its runtime value the duration contains a compile-time ratio specifying the units of time that value represents. 
    //      A ratio of 1:1000 means milliseconds, a ratio of 1:1,000,000 means microseconds. The default ratio is 1:1 – that is, the default units for durations is seconds.
    //  std::chrono::duration<>: represents time duration
    //      2 hours: a number (2) and a unit (hours)
    //  duration<int,ratio<1,1>>    	// number of seconds (because of ratio<1,1>) stored in an int
    //  duration<double,ratio<60,1>>    // number of minutes stored in a double
    //	duration<int,ratio<60*60*24>>	// number of days stored in an int
    //  chrono provides several predefined duration (typedef): nanoseconds (9 zeros), microseconds (6 zeros), milliseconds, seconds, minutes, hours
    //  each clock has its predefined duration:
    //      system_clock::duration  -- duration<T, system_clock::period> where T is any user-defined type (int, long)


    // clock frequency or period is represented by std::ratio
    ratio<1,10> r;  // 1/10
    cout << r.num << "/" << r.den << endl;  // print numerator and denominator

    cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << endl;

    chrono::microseconds mi(2700);
    mi.count();     // 2700
    cout << "mi.count: " << mi.count() << endl;
    chrono::nanoseconds na = mi;    // na is 2700000
    na.count();     // 2700000
    chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(mi);    // 2 milliseconds (it's truncated)

    mi = mill + mi;     // 2000 + 2700 = 4700

    chrono::system_clock::time_point tp = chrono::system_clock::now();
    // next statement returns number of clock cycles from now since time of epoch and
    // for example if the clock period is 1 nanoseconds (9 zeros) ...
    cout << tp.time_since_epoch().count() << endl;
    tp = tp + chrono::seconds(2);
    cout << tp.time_since_epoch().count() << endl;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "I'm bored" << endl;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::steady_clock::duration d = end - start;
    if (d == chrono::steady_clock::duration::zero())
        cout << "no time elapsed" << endl;
    cout << chrono::duration_cast<chrono::microseconds>(d).count() << endl;

	chrono::duration<int, ratio<60*60*24>> one_day(1);
	chrono::system_clock::time_point today = chrono::system_clock::now();
	chrono::system_clock::time_point tomorrow = today + one_day;
	time_t tt;
	tt = chrono::system_clock::to_time_t(today);
	cout << "today: " << ctime(&tt) << endl;
	tt = chrono::system_clock::to_time_t(tomorrow);
	cout << "tomorrow: " << ctime(&tt) << endl;

    return 0;
}
