#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>

class Buffer
{
    Q_OBJECT
    char *Buff;
    size_t Size;
    std::iostream &Stream;
    off_t Position;
    bool Dirty;
public:
    explicit Buffer(const size_t &bufferSize, std::iostream &stream,
                    const off_t &position, QObject *parent = nullptr);
    ~Buffer();
    const off_t &position();
    const size_t &size();
    const bool &dirty();
    std::iostream &stream();
    const char *rawData();
};

inline const off_t &Buffer::position()
{
    return Position;
}

inline const size_t &Buffer::size()
{
    return Size;
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

inline Buffer::Buffer(const size_t &bufferSize, std::iostream &stream,
               const off_t &position, QObject *parent)
    :QObject(parent), Buff(new char[bufferSize]),Size(bufferSize),
      Stream(stream), Position(position),Dirty(false)
{
    Stream.read(Buff,Size);
}

inline Buffer::~Buffer()
{
    delete [] Buff;
}

#endif // BUFFER_H
