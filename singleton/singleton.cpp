#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

class Singleton
{
    private:
        Singleton() {}
        static Singleton* instance_;
        static mutex mutex_;
        Singleton(const string value): value_(value) {}
        // ~Singleton();
        string value_;

    // protected:
        
        

    public:
        Singleton(Singleton& others) = delete;
        void operator=(Singleton& others) = delete;
        void SomeBusinessLogic()
        {
            //...
        };

        static Singleton *GetInstance(const string& value) 
        {
            lock_guard<mutex> lock(mutex_);
            if (instance_ == nullptr) 
            {
                instance_ = new Singleton(value);
            }
            return instance_;
        }

        string value() const {
            return value_;
        } 

};

Singleton* Singleton::instance_{nullptr};
mutex Singleton::mutex_;

void ThreadFoo() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main() {
    cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";   
    thread t1(ThreadFoo);
    thread t2(ThreadBar);
    t1.join();
    t2.join();
}   