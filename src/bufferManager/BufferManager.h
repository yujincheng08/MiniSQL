#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "Buffer.h"
#include "File.h"
#include <QObject>
#include <string>
#include <unordered_map>
#include <mutex>

class ReadThread;
class WriteThread;
class BufferManager : public QObject
{
    Q_OBJECT
    template<typename T, typename K>
    using HashMap = std::unordered_map<T,K>;
    using string = std::string;
    friend class File;
    friend class ReadThread;
private:
    ReadThread *readThread = nullptr;
    WriteThread *writeThread = nullptr;
    BufferList *list = Buffer::list();
    HashMap<string, File *> Files;
    File &Open(const string &fileName);
    std::mutex Mutex;
    static BufferManager &bufferManager();
    Buffer *buff(File *file, const Buffer::pos_type &pos, const Buffer::pos_type &size = Buffer::bufferSize());
    void preRead(File *file, const Buffer::pos_type &pos);
    void queueBuff(Buffer * const buffer);
    explicit BufferManager();
    void wait();
public:
    static File &open(const std::string &fileName);
    static size_t blockSize();

};

inline size_t BufferManager::blockSize()
{
    return 8192U;
}

#endif
