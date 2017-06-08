#ifndef BUFFER_H
#define BUFFER_H

#include <QIODevice>
#include <BufferListItem.h>
#include <mutex>
#include <cstring>
//Buffer of a file block
class QString;
class Buffer : protected BufferListItem
{
    friend class BufferManager;
    friend class File;
    friend class WriteThread;
public:
    using pos_type = std::streamoff;
private:
    static const size_t BufferSize;
    char *Buff;
    QIODevice &Stream;
    pos_type Position;
    pos_type Size;
    bool Dirty = false;
    bool InList = false;
    std::mutex Mutex;
private:
    static QString partition();
    explicit Buffer(QIODevice &stream,
                    const pos_type &position,
                    const size_t &empty = 0U);
    void write();
    void changeSize(const pos_type &size);
public:
    virtual ~Buffer();
    static size_t bufferSize();
};

inline Buffer::Buffer(QIODevice &stream,
                      const pos_type &position, const size_t &empty)
    : Buff(new char[bufferSize()]),
      Stream(stream), Position(position),Size(std::min(empty,bufferSize()))
{
    if(empty)
        memset(Buff,0, Size);
    else
    {
        Stream.seek(position);
        Size = Stream.read(Buff,bufferSize());
    }
}

inline void Buffer::write()
{
    Mutex.lock();
    Stream.seek(Position);
    Stream.write(Buff, Size);
    Mutex.unlock();
}

inline void Buffer::changeSize(const pos_type &size)
{
    if(size>Size)
        memset(Buff+Size,0,size-Size);
    //else
    Size=size;
}

inline Buffer::~Buffer()
{
    delete [] Buff;
}

inline size_t Buffer::bufferSize()
{
    return BufferSize;
}

#endif // BUFFER_H
