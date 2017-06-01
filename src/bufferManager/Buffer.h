#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>

//Buffer of a file block
class QString;
class Buffer
{
    char *Buff;
    static size_t BlockSize;
    size_t Size;
    std::iostream &Stream;
    off_t Position;
    bool Dirty;
private:
    static size_t calBlockSize();
    static QString partition();
public:
    explicit Buffer(std::iostream &stream,
                    const off_t &position);
    ~Buffer();
    const off_t &position();
    const bool &dirty();
    std::iostream &stream();
    const char *rawData();
    static size_t blockSize();
};

inline const off_t &Buffer::position()
{
    return Position;
}

inline const bool &Buffer::dirty()
{
    return Dirty;
}

inline std::iostream &Buffer::stream()
{
    return Stream;
}

inline const char *Buffer::rawData()
{
    return Buff;
}

inline Buffer::Buffer(std::iostream &stream,
               const off_t &position)
    : Buff(new char[blockSize()]),
      Stream(stream), Position(position),Dirty(false)
{
    Stream.read(Buff,blockSize());
    Size = Stream.gcount();
}

inline Buffer::~Buffer()
{
    delete [] Buff;
}

inline size_t Buffer::blockSize()
{
    if(BlockSize)
        return BlockSize;
    else
        return BlockSize = calBlockSize();
}

#endif // BUFFER_H
