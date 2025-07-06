#include "../include/logger.h"
#include <iostream>
#include <ctime>
using namespace std;

string Time()
{
    time_t t = time(nullptr);
    char* tstr = ctime(&t); 
    return tstr;
}

extern string StringLogLvl(LogLvl lvl)
{
    if(lvl == INFO) return "INFO";
    else if(lvl == ERROR) return "ERROR";
    else if(lvl == CRITICAL) return "CRITICAL";
    else return "NOTSET";
}

extern LogLvl StrToLogLvl(string str)
{
    if(str == "INFO") return INFO;
    else if(str == "ERROR") return ERROR;
    else if(str == "CRITICAL") return CRITICAL;
    else return NOTSET;
}

Message::Message(const string str, LogLvl lvl)
{
    text = str;
    mLvl = lvl;
    time = Time();
}
Message::~Message()
{

}

string Message::GetText()
{
    return text;
}

LogLvl Message::GetLvl()
{
    return mLvl;
}

string Message::GetTime()
{
    return time;
}

bool Message::IsRecord(LogLvl lvl)
{
    if(GetLvl()>=lvl)
        return true;
    else return false;
}

Logger::Logger(const string filename, LogLvl lvl)
{
    minLvl = lvl;
    LogFile.open(filename);
    if (!LogFile.is_open())
    {
        cerr<<"File "<<filename<<" not open!"<<endl;
    }
}

Logger::~Logger()
{
    LogFile.close();
}

void Logger::SetLvl(LogLvl newlvl)
{
    minLvl = newlvl;
}

void Logger::Record(Message str)
{
    LogFile<<str.GetText()<<" ["<<StringLogLvl(str.GetLvl())<<"]"<<" "<<str.GetTime();
}

LogLvl Logger::GetLvl()
{
    return minLvl;
}
