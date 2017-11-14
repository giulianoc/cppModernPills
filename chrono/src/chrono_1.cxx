#include <chrono>
#include <iostream>

using namespace std;

int main()
{
    // chrono: a precision-neutral libraru for time and date
    //  it separates duration and time point from the clock

    // Clock:
    //  std::chrono::system_clock: current time according to the system
    //  std::chrono::steady_clock: goes at uniform rate (this is not always like the system_clock because the system clock
    //      can be modified by the user, I mean if the user move the system time 2 hours later, looking at the system_clock
    //      seems like 2 hours passed, steady_clock even in this case, say it is passed just 2 minutes for example)
    //  std::chrono::high_resolution_clock: provides smallest possible tick period. This is in case we need an high resolution for the clock

    // Duration:
    //  std::chrono::duration<>: represents time duration
    //      2 hours: a number (2) and a unit (hours)
    //  duration<int,ratio<1,1>>    // number of seconds (because of ratio<1,1>) stored in an int
    //  duration<double,ratio<60,1>>    // number of minutes stored in a double
    //  chrono provides several predefined duration (typedef): nanoseconds, microseconds, milliseconds, seconds, minutes, hours
    //  each clock has its predefined duration:
    //      system_clock::duration  -- duration<T, system_clock::period> where T is any user-defined type (int, long)

    // clock frequency or period is represented by std::ratio
    ratio<1,10> r;  // 1/10
    cout << r.num << "/" << r.den << endl;  // print numerator and denominator

    cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << endl;

    chrono::microseconds mi(2700);
    mi.count();     // 2700
    chrono::nanoseconds na = mi;    // na is 2700000
    na.count();     // 2700000
    chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(mi);    // 2 milliseconds (it's truncated)

    mi = mill + mi;     // 2000 + 2700 = 4700


    return 0;
}
