#include "BufferManager.h"
#include "ReadThread.h"
#include "WriteThread.h"
using namespace std;

BufferManager &BufferManager::bufferManager()
{
    static BufferManager bm;
    return bm;
}

File &BufferManager::open(const string &fileName)
{
    return bufferManager().Open(fileName);
}

Buffer *BufferManager::buff(File *file, const Buffer::pos_type &pos, const Buffer::pos_type &size)
{
    Mutex.lock();
    Buffer *buffer = nullptr;
    if(!file->Exist(pos))
    {
        if(pos>file->Stream.size())
            buffer = new Buffer(file->Stream,pos,size);
        else
            buffer = new Buffer(file->Stream,pos);
        file->Insert(buffer);
    }
    else
        buffer = file->GetBuffer(pos);
    Mutex.unlock();
    return buffer;
}

void BufferManager::preRead(File *file, const Buffer::pos_type &pos)
{
    readThread->setNext(file, pos);
}

void BufferManager::queueBuff(Buffer * const buffer)
{
    writeThread->enQueue(buffer);
}

BufferManager::BufferManager()
    :readThread(new ReadThread()),writeThread(new WriteThread())
{}

File &BufferManager::Open(const string &fileName)
{
    auto i = Files.find(fileName);
    if(i == Files.end())
    {
        File *file = new File(fileName);
        Files.insert(std::make_pair(fileName,file));
        return *file;
    }
    else
        return *i->second;
}

void BufferManager::wait()
{
    writeThread->wait();
}
