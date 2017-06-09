#include "WriteThread.h"
#include <iostream>
void WriteThread::run()
{
    while(!WriteList.empty())
    {
        Mutex.lock();
        auto i = WriteList.front();
        i->write();
        i->Dirty = false;
        WriteList.pop_front();
        Mutex.unlock();
    }
    std::cout<<"Writing done."<<std::endl;
    quit();
}
