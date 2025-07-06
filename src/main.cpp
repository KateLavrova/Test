#include "../include/logger.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <unistd.h>
#include <string>
#include <queue>

using namespace std;

queue<Message*> mesQueue;
mutex mtx;
mutex mtx_ex;

void InputMes(bool &ex)
{
    while(!ex)
    {
        cout<<"Введите сообщение: ";
        string textMessage;
        getline(cin,textMessage);
        if (textMessage == "exit") 
        {
            mtx_ex.lock();
            ex = true; 
            mtx.unlock();  
        }
        else 
        {
            cout<<"Введите уровень важности: "; 
            string lvl;
            getline(cin, lvl);
            LogLvl lvlMessage = StrToLogLvl(lvl);
            Message *m = new Message(textMessage,lvlMessage);
            mtx.lock();
            mesQueue.push(m);
            mtx.unlock();
        }
    }
}

void OutputMes(bool &ex, Logger &L)
{
    while(!ex)
    {
        mtx.lock();
        if(!mesQueue.empty())
        {
            L.Record(*mesQueue.front());
            mesQueue.pop();
            mtx.unlock();
        }
        else 
        {
            mtx.unlock();
            this_thread::sleep_for(100ms);
        }
    }
}

int main() 
{

    string name;
    cout<<"Введите имя файла журнала: ";
    getline(cin, name);
    const string filename = name;
    string lvl;
    cout<<"Введите уровень важности сообщения по умолчанию: ";
    getline(cin, lvl);
    LogLvl lvlDefault = StrToLogLvl(lvl);
    Logger L(filename, lvlDefault);

    bool ex = false; 
    thread threadMes(InputMes, ref(ex));
    thread threadWrite(OutputMes, ref(ex), ref(L));
    threadMes.join();
    threadWrite.join();
	return 0;
}