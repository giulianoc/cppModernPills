#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>
#include <future>


using namespace std;

void function_1(string msg)
{
    cout << msg << endl;
}

class Fctor1 {
public:
    void operator ()(string& msg) {
        cout << "t1 says: " << msg << endl;
        msg = "Trust is the mother of deceit";
    }
};

class LogFile {
    mutex m_mutex;
    ofstream f;
public:
    LogFile(){
        // f.open("log.txt");
    }
    // need constructor to close the file...
    
    void sharedPrint(string msg, int value)
    {
        // One option to set the lock is using m_mutex.lock() and m_mutex.unlock().
        // That option is not ideal because in case we have an exception between lock and unlock
        // the lock will remain forever.
        // The correct option to be used is lock_guard
        lock_guard<mutex> locker(m_mutex);
        cout << "From " << msg << ": " << value << endl;
        
        // The previous lock_guard locks the mutex at the beginning and unlocks it
        // when locker is out of the scope. In case we need more flexibility and unlock before the out
        // of scope, we have to use unique_lock:
        // 1. unique_lock<mutex> locker(m_mutex);  // lock the mutex or
        // 2. unique_lock<mutex> locker(m_mutex, defer_lock);  // it does not lock the mutex
        // In any time we can lock or unlock the mutex
        // Anyway, if we do not need this flexibility, it would be better from performance
        // point of view using lock_guard
    }
};

void function_2(LogFile& log)
{
    for (int i = 0; i > -100; i--)
       log.sharedPrint("From t1 ", i);
}

deque<int> q;
mutex mu;
condition_variable cond;

void producer()
{
    int count = 10;
    
    while (count > 0)
    {
        unique_lock<mutex> locker(mu);
        q.push_front(count);
        locker.unlock();
        cond.notify_one();  // notify one waiting thread, if there is one
        // cond.notify_all();
        this_thread::sleep_for(chrono::seconds(1));
        count--;
    }
}

void consumer()
{
    int data = 0;
    while(data != 1)
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){ return !q.empty(); });  // lambda function to manage spurious wake
        // wait and wait_for without the lambda function return: cv_status::timeout or cv_status::notimeout
        data = q.back();
        q.pop_back();
        locker.unlock();
        cout << "t2 got a value from t1: " << data << endl;
    }
}

int factorial (int N)
{
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;
        
    return res;
}

int factorial2 (future<int>& f)
{
    int N = f.get();    // in case promise is broken (p.set_value is not called), exception std::future_errc::broken_promise is raised
    
    int res = 1;
    for (int i = N; i > 1; i--)
        res *= i;
        
    return res;
}

int main(int argc, char** argv) 
{
    // t1 will be destroyed if it goes out of scope
    // so t1 has to be join or detach.
    // To make sure t1 is join (t.join()) or detach (t.detach()), we can use RAII

    {
        string s = "Beauty is only skin-deep";
        thread t1 (function_1, s);
        t1.join();
    }

    {
        // Next we will pass a string by reference. This is not really correct
        // because of data race issues
        string s = "Where there is no trust, there is no love";

        Fctor1 fct1;
        thread t1(fct1, std::ref(s));
        cout << "t1 id: " << t1.get_id() << endl;   // id of the main thread
        cout << "from main " << s << endl;
        t1.join();
        cout << "from main " << s << endl;

        cout << "main thread id: " << this_thread::get_id() << endl;   // id of the main thread
    }

    {
        // it is a good approach to avoid to create more threads than the number of Cores (CPU)
        // Otherwise we will have a lot of context switching degrading the performance (Oversubscription)
        cout << "concurrent thread supports by current hardware (it's an indication): " << thread::hardware_concurrency() << endl;
    }    
    
    {
        LogFile log;
        
        thread t1 (function_2, ref(log));
        for (int i = 0; i < 100; i++)
            log.sharedPrint("From main ", i);
        t1.join();
    }
    
    {
        thread t1 (producer);
        thread t2 (consumer);
        t1.join();
        t2.join();
    }
    
    {
        int x;
        // future represents an object where you can get something in the future
        // async may or may not create another thread.
        //      async(launch::deferred, factorial, 4);  called factorial when fu.get is called and it is used the same thread no new thread is created
        //      async(launch::async, factorial, 4);  creates another thread
        //      async(launch::deferred | launch::async, factorial, 4);  implementation decides to create or not a thread
        future<int> fu = async(factorial, 4);
        x = fu.get();   // wait until the child thread will finish. fu.get() can be called only once
        
        cout << "factorial(" << 4 << ") is " << x << endl;
    }
    
    {
        // we can use future to pass a parameter from parent to child thread
        int x;
        promise<int> p;
        future<int> f = p.get_future();

        future<int> fu = async(factorial2, ref(f));
        
        // sometime later
        this_thread::sleep_for(chrono::seconds(1));
        p.set_value(4);
        
        // if we cannot set the promise, we can cause a custom exception
        // p.set_exception(make_exception_ptr(runtime_error("To err is human")));
        
        x = fu.get();   // wait until the child thread will finish. fu.get() can be called only once

        cout << "factorial(" << 4 << ") is " << x << endl;
    }
    
    // different ways to call a thread
    {
        string s = "Where there is no trust, there is no love";
        Fctor1 f;

        thread t1(f, std::ref(s));   // copy of f() in a different thread 
        t1.join();
  
        thread t2(ref(f), std::ref(s));   // f() in a different thread 
        t2.join();
        
        thread t3(Fctor1(), std::ref(s));   // temp Fctor() in a different thread 
        t3.join();

        thread t4([](string s) { cout << s << endl; }, s); 
        t4.join();

        /*
         to call a method of a class as thread:
        class DummyClass {
        public:
            DummyClass()
            {}
            DummyClass(const DummyClass & obj)
            {}
            void sampleMemberFunction(int x)
            {
                std::cout<<"Inside sampleMemberFunction "<<x<<std::endl;
            }
        };
         * 
        DummyClass dummyObj;
        int x = 10;
        std::thread threadObj(&DummyClass::sampleMemberFunction,&dummyObj, x);
        threadObj.join();
         */

        
        // other funtions creating threads: async(), call_once()
        // once_flag _flag;
        // call_once(_flag, [&](){ _f.open("log.txt"); }); // file will be opened only once by one thread
    }

    return 0;
}

