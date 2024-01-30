#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
    // Regular expression: specific pattern that provides concise and flexible means
    //	to "match" strings of text

    if(false)
    {
		string str;

        cout << "Write Email address to parse: ";
        cin >> str;

        // Next I want to extract a portion of the email address, for example the username and domain
        // First I have to define the groups (submatch) to define username e domain name
        {
            smatch m;   // typedef std:match_result<string>

            regex e("([[:w:]]+)@([[:w:]]+)\.com");

            bool match = regex_search(str, m, e);

            // m is where the result is saved
            // we will have three results: the entire match, the first submatch, the second submatch
            // giving the following input: <email>user@gmail.com<end>
            // m.prefix(): everything is in front of the matched string (<email> in the previous example)
            // m.suffix(): everything is after the matched string (<end> in the previous example)

            cout << "m.size() " << m.size() << endl;
            for (int n = 0; n < m.size(); n++)
            {
                cout << "m[" << n << "]: str()=" << m[n].str() << endl; // m.str(n) and *(m.begin()+n) provides same result
            }
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
        }
    }
    
    if(false)
    {
		string str;

        cout << "Write URL to parse: ";
        cin >> str;

        // URL parse
        {
            smatch m;   // typedef std:match_result<string>

            // regex e("(http|https|ftp)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
            regex e (R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", std::regex::extended);

            bool match = regex_search(str, m, e);   // return true if it matches

//            Checking: http://localhost.com/path?hue=br#cool
//            0: http://localhost.com/path?hue=br#cool
//            1: http:
//            2: http
//            3: //localhost.com
//            4: localhost.com
//            5: /path
//            6: ?hue=br
//            7: hue=br
//            8: #cool
//            9: cool
            
            cout << "m.size() " << m.size() << endl;
            for (int n = 0; n < m.size(); n++)
            {
                cout << "m[" << n << "]: str()=" << m[n].str() << endl; // m.str(n) and *(m.begin()+n) provides same result
            }
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
        }
    }

    // get duration in millisecs (Duration: 00:17:41.32) from the ffmpeg -i output
    if(false)
    {
        string ffmpegOutput =
"ffmpeg version 3.4.1 Copyright (c) 2000-2017 the FFmpeg developers\n"
"  built with gcc 7 (Ubuntu 7.2.0-8ubuntu3)\n"
"  configuration: --prefix=/app/7/DevelopmentWorkingArea/usr_local --enable-libmp3lame --enable-libopus --enable-libx265 --enable-gpl --enable-libfdk-aac --enable-libvpx --enable-libx264 --enable-nonfree --enable-shared --enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libvorbis --enable-libxvid --enable-version3\n"
"  libavutil      55. 78.100 / 55. 78.100\n"
"  libavcodec     57.107.100 / 57.107.100\n"
"  libavformat    57. 83.100 / 57. 83.100\n"
"  libavdevice    57. 10.100 / 57. 10.100\n"
"  libavfilter     6.107.100 /  6.107.100\n"
"  libswscale      4.  8.100 /  4.  8.100\n"
"  libswresample   2.  9.100 /  2.  9.100\n"
"  libpostproc    54.  7.100 / 54.  7.100\n"
"Input #0, mpeg, from '/home/giuliano/storage/CMSRepository/CMS_0000/Warner/000/000/002/UN_BOSS_IN_SALOTTO.mpg':\n"
"  Duration: 00:17:41.32, start: 0.339378, bitrate: 5398 kb/s\n"
"    Stream #0:0[0x1e0]: Video: mpeg2video (Main), yuv420p(tv, bottom first), 720x576 [SAR 64:45 DAR 16:9], 5000 kb/s, 25 fps, 25 tbr, 90k tbn, 50 tbc\n"
"    Stream #0:1[0x1c0]: Audio: mp2, 48000 Hz, stereo, s16p, 192 kb/s\n"
"At least one output file must be specified\n";

        smatch m;   // typedef std:match_result<string>

        regex e("Duration: ([^,]+)");

        bool match = regex_search(ffmpegOutput, m, e);

        // m is where the result is saved
        // we will have three results: the entire match, the first submatch, the second submatch
        // giving the following input: <email>user@gmail.com<end>
        // m.prefix(): everything is in front of the matched string (<email> in the previous example)
        // m.suffix(): everything is after the matched string (<end> in the previous example)

        cout << "m.size() " << m.size() << endl;
        for (int n = 0; n < m.size(); n++)
        {
            cout << "m[" << n << "]: str()=" << m[n].str() << endl; // m.str(n) and *(m.begin()+n) provides same result
        }
        cout << "m.prefix().str(): " << m.prefix().str() << endl;
        cout << "m.suffix().str(): " << m.suffix().str() << endl;
        
        if (m.size() >= 2)
        {
            string duration = m[1].str();
            
            // split the string (got from string.cxx pill)
            vector<string> timeElements;
            stringstream ss(duration);
            string hours;
            string minutes;
            string seconds;
            string microseconds;    // microseconds???
            char delim = ':';

            getline(ss, hours, delim); 
            if (hours.empty())
                ; // error

            getline(ss, minutes, delim); 
            if (minutes.empty())
                ; // error

            delim = '.';
            getline(ss, seconds, delim); 
            if (seconds.empty())
                ; // error

            getline(ss, microseconds, delim); 
            if (microseconds.empty())
                ; // error

            cout << "result:" << endl;
            cout << hours << endl;        
            cout << minutes << endl;        
            cout << seconds << endl;        
            cout << microseconds << endl;        
        }
    }

    if(true)
    {
		string str = "https://rsi.cue.rsi.ch/sport/sci-alpino/2055053-5ixsyt-lara-gut-behrami";

        // Next I want to extract a portion of the email address, for example the username and domain
        // First I have to define the groups (submatch) to define username e domain name
        {
            smatch m;   // typedef std:match_result<string>

			regex alternateRegex("/([A-Za-z0-9\-\_]+)/([A-Za-z0-9\-\_]+)/([A-Za-z0-9\-\_]+)");

            bool match = regex_search(str, m, alternateRegex);

            // m is where the result is saved
            // we will have three results: the entire match, the first submatch, the second submatch
            // giving the following input: <email>user@gmail.com<end>
            // m.prefix(): everything is in front of the matched string (<email> in the previous example)
            // m.suffix(): everything is after the matched string (<end> in the previous example)

            cout << "m.size() " << m.size() << endl;
            for (int n = 0; n < m.size(); n++)
            {
                cout << "m[" << n << "]: str()=" << m[n].str() << endl; // m.str(n) and *(m.begin()+n) provides same result
            }
            cout << "m.prefix().str(): " << m.prefix().str() << endl;
            cout << "m.suffix().str(): " << m.suffix().str() << endl;
        }
    }
}
