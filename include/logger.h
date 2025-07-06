#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
using namespace std;

enum LogLvl : int {CRITICAL = 3, ERROR = 2, INFO = 1, NOTSET = 0};

class __attribute__((visibility("default"))) Message;
class __attribute__((visibility("default"))) Logger;

extern string StringLogLvl(LogLvl lvl);
extern LogLvl StrToLogLvl(string lvl);

class Message
{
    private:
        string text;
        LogLvl mLvl;
        string time;

    public:
        Message(const string str, LogLvl lvl);
        ~Message();
        string GetText();
        LogLvl GetLvl();
        string GetTime();
        bool IsRecord(LogLvl lvl);
};

class Logger 
{
    public:
        Logger(const string filename, LogLvl lvl);
        ~Logger();
        void SetLvl(LogLvl newlvl);
        LogLvl GetLvl();
        void Record(Message str);
        
    private:
        ofstream LogFile;
        LogLvl minLvl;
};

#endif