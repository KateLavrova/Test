#include "../include/logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;

void testStrToLogLvl() 
{
    cout<<"Running testStrToLogLvl... ";
    if((StrToLogLvl("CRITICAL") == LogLvl::CRITICAL) && (StrToLogLvl("ERROR") == LogLvl::ERROR) && (StrToLogLvl("INFO") == LogLvl::INFO) && (StrToLogLvl("no") == LogLvl::NOTSET))
        cout<<"OK"<<endl;
    else cout<<"NOT OK"<<endl;
}

void testStringLogLvl()
{
    cout<<"Running testStrToLogLvl... ";
    if((StringLogLvl(LogLvl::CRITICAL) == "CRITICAL") && (StringLogLvl(LogLvl::ERROR) == "ERROR") && (StringLogLvl(LogLvl::INFO) == "INFO") && (StringLogLvl(LogLvl::NOTSET) == "NOTSET"))
        cout<<"OK"<<endl;
    else cout<<"NOT OK";
}

void testMessage()
{
    cout<<"Running testMessage... ";
    Message m("test", LogLvl::CRITICAL);
    if((m.GetText() == "test") && (m.GetLvl() == LogLvl::CRITICAL))
        cout<<"OK"<<endl;
    else cout<<"NOT OK"<<endl;

    cout<<"Running testMessageIsRecord... ";
    bool flag = (m.IsRecord(LogLvl::CRITICAL) == true) && (m.IsRecord(LogLvl::ERROR) == true) && (m.IsRecord(LogLvl::INFO) == true) && (m.IsRecord(LogLvl::NOTSET) == true);

    Message m1("test", LogLvl::ERROR);
    bool flag1 = (m1.IsRecord(LogLvl::CRITICAL) == false) && (m1.IsRecord(LogLvl::ERROR) == true) && (m1.IsRecord(LogLvl::INFO) == true) && (m1.IsRecord(LogLvl::NOTSET) == true);
    
    Message m2("test", LogLvl::INFO);
    bool flag2 = (m2.IsRecord(LogLvl::CRITICAL) == false) && (m2.IsRecord(LogLvl::ERROR) == false) && (m2.IsRecord(LogLvl::INFO) == true) && (m2.IsRecord(LogLvl::NOTSET) == true);

    Message m3("test", LogLvl::NOTSET);
    bool flag3 = (m3.IsRecord(LogLvl::CRITICAL) == false) && (m3.IsRecord(LogLvl::ERROR) == false) && (m3.IsRecord(LogLvl::INFO) == false) && (m3.IsRecord(LogLvl::NOTSET) == true);

    if(flag && flag1 && flag2 && flag3)
        cout<<"OK"<<endl;
    else cout<<"NOT OK"<<endl;
}

void testLogger()
{
    cout<<"Running testLogger... ";
    string file = "testFile";
    Message m1("Critical message", LogLvl::CRITICAL);
    Message m2("Error message", LogLvl::ERROR);
    Message m3("Info message", LogLvl::INFO);
    Message m4("Notset message", LogLvl::NOTSET);
    {
        ofstream testFile;
        Logger l(file, LogLvl::CRITICAL);
        bool k = (l.GetLvl() == LogLvl::CRITICAL);
        l.SetLvl(LogLvl::INFO);
        if(l.GetLvl()==LogLvl::INFO) 
            cout<<"OK"<<endl;
        else cout<<"NOT OK"<<endl;

        cout<<"Running testLoggerRecord... ";
        l.Record(m1);
        l.Record(m2);
        l.Record(m3);
        l.Record(m4);
    }

    ifstream testFileIn;
    testFileIn.open(file);
    string line1,line2,line3,line4; 
    getline(testFileIn, line1);
    getline(testFileIn, line2);
    getline(testFileIn, line3);
    getline(testFileIn, line4);
    
    string k1 = "Critical message [CRITICAL] " + m1.GetTime();
    string k2 = "Error message [ERROR] " + m2.GetTime();
    string k3 = "Info message [INFO] " + m3.GetTime();
    string k4 = "Notset message [NOTSET] " + m4.GetTime();

    if( ((line1 + "\n") == k1) && ((line2 + "\n") == k2) && ((line3 + "\n") == k3) && ((line4 + "\n") == k4)) 
        cout<<"OK"<<endl;
    else cout<<"NOT OK"<<endl;
    testFileIn.close();
    filesystem::remove(file);
}

int main() 
{
    testStrToLogLvl();
    testStringLogLvl();
    testMessage();
    testLogger();
    cout << "All tests completed!\n";
    return 0;
}