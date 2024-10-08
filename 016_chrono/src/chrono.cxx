#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  // chrono: a precision-neutral library for time and date
  //  it separates duration and time point from the clock

  // Clocks (are time providers, consisting of a starting point (“epoch”) and a
  // tick rate):
  //  std::chrono::system_clock: current time according to the system
  //  std::chrono::steady_clock: goes at uniform rate (this is not always like
  //  the system_clock because the system clock
  //      can be modified by the user, I mean if the user move the system time 2
  //      hours later, looking at the system_clock seems like 2 hours passed,
  //      steady_clock even in this case, say it is passed just 2 minutes for
  //      example)
  //  std::chrono::high_resolution_clock: provides smallest possible tick
  //  period. This is in case we need an high resolution for the clock

  // Time point:
  //  - represents how much time has passed since the start of the clock
  //  - You won’t be able to initialise it with the now() of a different clock
  //  because its time_point type isn’t convertible to that of the original
  //  clock
  //  - It can be added to and subtracted from other time_point instances):
  //  std::chrono::time_point<>:  represent a point of time starting from 00:00
  //  January 1970 (UTC) - epoch of clock time_point<system_clock,
  //  milliseconds>: the elapsed time since epoch in milliseconds, according to
  //  system_clock Each clock has its own time_point definition:
  //      system_clock::time_point    -- time_point<system_clock,
  //      system_clock::duration> steady_clock::time_point    --
  //      time_point<steady_clock, system_clock::duration>

  // Duration:
  //  - A duration is, like a time_point, just a puffed-up arithmetic type.
  //  - Unlike time_point, it’s not coupled to a specific clock type at compile
  //  time.
  //  - Along with its runtime value the duration contains a compile-time ratio
  //  specifying the units of time that value represents.
  //      A ratio of 1:1000 means milliseconds, a ratio of 1:1,000,000 means
  //      microseconds. The default ratio is 1:1 – that is, the default units
  //      for durations is seconds.
  //  std::chrono::duration<>: represents time duration
  //      2 hours: a number (2) and a unit (hours)
  //  duration<int,ratio<1,1>>    	// number of seconds (because of
  //  ratio<1,1>) stored in an int duration<double,ratio<60,1>>    // number of
  //  minutes stored in a double duration<int,ratio<60*60,1>>    // number of
  //  hours stored in a int
  //	duration<int,ratio<60*60*24>>	// number of days stored in an int
  //  chrono provides several predefined duration (typedef): nanoseconds (9
  //  zeros), microseconds (6 zeros), milliseconds, seconds, minutes, hours each
  //  clock has its predefined duration:
  //      system_clock::duration  -- duration<T, system_clock::period> where T
  //      is any user-defined type (int, long)

  // clock frequency or period is represented by std::ratio
  ratio<1, 10> r;                        // 1/10
  cout << r.num << "/" << r.den << endl; // print numerator and denominator

  cout << chrono::system_clock::period::num << "/"
       << chrono::system_clock::period::den << endl;

  chrono::microseconds mi(2700);
  mi.count(); // 2700
  cout << "mi.count: " << mi.count() << endl;
  chrono::nanoseconds na = mi; // na is 2700000
  na.count();                  // 2700000
  chrono::milliseconds mill = chrono::duration_cast<chrono::milliseconds>(
      mi); // 2 milliseconds (it's truncated)

  mi = mill + mi; // 2000 + 2700 = 4700

  chrono::system_clock::time_point tp = chrono::system_clock::now();
  // next statement returns number of clock cycles from now since time of epoch
  // and for example if the clock period is 1 nanoseconds (9 zeros) ...
  cout << tp.time_since_epoch().count() << endl;
  tp = tp + chrono::seconds(2);
  cout << tp.time_since_epoch().count() << endl;

  chrono::steady_clock::time_point start = chrono::steady_clock::now();
  cout << "I'm bored" << endl;
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  chrono::steady_clock::duration d = end - start;
  if (d == chrono::steady_clock::duration::zero())
    cout << "no time elapsed" << endl;
  cout << "microseconds: "
       << chrono::duration_cast<chrono::microseconds>(d).count() << endl;
  cout << "hours: " << chrono::duration_cast<chrono::hours>(d).count() << endl;
  if (chrono::duration_cast<chrono::hours>(d) >= chrono::hours(1))
    cout << "duration in hours is >= 1 hours" << endl;
  else
    cout << "duration in hours is not >= 1 hours" << endl;

  chrono::duration<int, ratio<60 * 60 * 24>> one_day(1);
  chrono::system_clock::time_point today = chrono::system_clock::now();
  chrono::system_clock::time_point tomorrow = today + one_day;

  time_t utcTime;
  utcTime = chrono::system_clock::to_time_t(today);
  // to get chrono from time_t: chrono::system_clock::time_point t =
  // chrono::system_clock::from_time_t(utcTime)
  cout << "today: " << ctime(&utcTime) << endl;
  utcTime = chrono::system_clock::to_time_t(tomorrow);
  cout << "tomorrow: " << ctime(&utcTime) << endl;

  // now local time as string (chrono to string)
  {
    tm tmDateTime;
    char strDateTime[64];

    localtime_r(&utcTime, &tmDateTime);

    sprintf(strDateTime, "%04d-%02d-%02d %02d:%02d:%02d",
            tmDateTime.tm_year + 1900, tmDateTime.tm_mon + 1,
            tmDateTime.tm_mday, tmDateTime.tm_hour, tmDateTime.tm_min,
            tmDateTime.tm_sec);

    cout << "tomorrow: " << strDateTime << endl;
  }

  // now utc as string (chrono to string)
  {
    tm tmDateTime;
    char strDateTime[64];

    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t utcNow = chrono::system_clock::to_time_t(now);

    gmtime_r(&utcNow, &tmDateTime);
    sprintf(strDateTime, "%04d-%02d-%02dT%02d:%02d:%02dZ",
            tmDateTime.tm_year + 1900, tmDateTime.tm_mon + 1,
            tmDateTime.tm_mday, tmDateTime.tm_hour, tmDateTime.tm_min,
            tmDateTime.tm_sec);

    cout << "tomorrow: " << strDateTime << endl;
  }

  // comparing time_point
  {
    chrono::milliseconds ms(10);
    chrono::system_clock::time_point now = chrono::system_clock::now();
    chrono::system_clock::time_point nowPlus = now - ms;

    if (now < nowPlus)
      cout << "now is < nowPlus" << endl;
    else
      cout << "now is not < nowPlus" << endl;
  }

  // comparing a date time string
  {
    string strdateTime_1("2018-03-26 13:28:00");

    char dateTime_2[64];
    {
      int numberOfHours = 1;

      chrono::system_clock::time_point now = chrono::system_clock::now();
      chrono::system_clock::time_point retentionDateTime =
          now - chrono::hours(numberOfHours);

      time_t retentionUtcTime;
      retentionUtcTime = chrono::system_clock::to_time_t(retentionDateTime);

      tm retentionTmDateTime;

      localtime_r(&retentionUtcTime, &retentionTmDateTime);

      sprintf(dateTime_2, "%04d-%02d-%02d %02d:%02d:%02d",
              retentionTmDateTime.tm_year + 1900,
              retentionTmDateTime.tm_mon + 1, retentionTmDateTime.tm_mday,
              retentionTmDateTime.tm_hour, retentionTmDateTime.tm_min,
              retentionTmDateTime.tm_sec);
    }

    if (strdateTime_1 < string(dateTime_2))
      cout << strdateTime_1 << " < " << string(dateTime_2) << endl;
    else
      cout << strdateTime_1 << " >= " << string(dateTime_2) << endl;
  }

  // to get monday of the current week
  {
    tm tmDateTime;

    today = chrono::system_clock::now();
    utcTime = chrono::system_clock::to_time_t(today);

    localtime_r(&utcTime, &tmDateTime);
    // tmDateTime.tm_wday: 0-6, 0 is Sunday

    int daysToHavePreviousMonday;

    if (tmDateTime.tm_wday == 0) // Sunday
      daysToHavePreviousMonday = 6;
    else
      daysToHavePreviousMonday = tmDateTime.tm_wday - 1;

    cout << "days to be subtracted: " << daysToHavePreviousMonday << endl;
    chrono::system_clock::time_point mondayOfCurrentWeek;
    if (daysToHavePreviousMonday != 0) {
      chrono::duration<int, ratio<60 * 60 * 24>> days(daysToHavePreviousMonday);
      mondayOfCurrentWeek = today - days;
    } else
      mondayOfCurrentWeek = today;

    utcTime = chrono::system_clock::to_time_t(mondayOfCurrentWeek);
    cout << "mondayOfCurrentWeek: " << ctime(&utcTime) << endl;
  }

  // to get sunday of the current week
  {
    tm tmDateTime;

    today = chrono::system_clock::now();
    utcTime = chrono::system_clock::to_time_t(today);

    localtime_r(&utcTime, &tmDateTime);
    // tmDateTime.tm_wday: 0-6, 0 is Sunday

    int daysToHaveNextSunday;

    daysToHaveNextSunday = 7 - tmDateTime.tm_wday;

    cout << "days to be added: " << daysToHaveNextSunday << endl;
    chrono::system_clock::time_point sundayOfCurrentWeek;
    if (daysToHaveNextSunday != 0) {
      chrono::duration<int, ratio<60 * 60 * 24>> days(daysToHaveNextSunday);
      sundayOfCurrentWeek = today + days;
    } else
      sundayOfCurrentWeek = today;

    utcTime = chrono::system_clock::to_time_t(sundayOfCurrentWeek);
    cout << "sundayOfCurrentWeek: " << ctime(&utcTime) << endl;
  }

  // to get the last day of the current month
  {
    tm tmDateTime;

    today = chrono::system_clock::now();
    utcTime = chrono::system_clock::to_time_t(today);

    localtime_r(&utcTime, &tmDateTime);

    tmDateTime.tm_mday = 1;

    // Next month 0=Jan
    if (tmDateTime.tm_mon == 11) // Dec
    {
      tmDateTime.tm_mon = 0;
      tmDateTime.tm_year++;
    } else {
      tmDateTime.tm_mon++;
    }

    // Get the first day of the next month
    utcTime = mktime(&tmDateTime);

    // Subtract 1 day
    utcTime -= 86400;

    // Convert back to date and time
    localtime_r(&utcTime, &tmDateTime);

    cout << "last day of the current month: " << ctime(&utcTime) << endl;
  }

  // string to chrono (for 'chrono to string' see above)
  {
    tm tm = {};
    stringstream ss("Jan 9 2014 12:35:34");
    ss >> get_time(&tm, "%b %d %Y %H:%M:%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    time_t utcTime = chrono::system_clock::to_time_t(tp);
    cout << "string to chrono (1): " << ctime(&utcTime) << endl;
  }
  {
    string s = "2024-09-02T19:00:49.000Z";
    tm tm = {};
    stringstream ss(s);
    ss >> get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    time_t utcTime = chrono::system_clock::to_time_t(tp);
    cout << "string to chrono (" + s + "): " << ctime(&utcTime) << endl;
  }

  return 0;
}
