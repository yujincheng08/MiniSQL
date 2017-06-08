#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <type_traits>
#include <unordered_map>
#include <QObject>
#include "Buffer.h"
class Buffer;
class File : public QObject
{
    Q_OBJECT
    friend class BufferManager;
    friend class ReadThread;
public:
    template<bool T, class K = void>
    using enable_if = typename std::enable_if<T,K>::type;
    template<typename T>
    using Valid = enable_if<!std::is_class<T>::value && !std::is_pointer<T>::value, T>;
    template<typename T, typename K>
    using HashMap = std::unordered_map<T,K>;
    using string = std::string;
    using pos_type = std::streamoff;
private:
    QFile Stream;
    pos_type FileSize;
    size_t BlockCount;
    pos_type ReadCursor = 0;
    pos_type WriteCursor = 0;
    HashMap<size_t, Buffer *> Buffers; //pos = first * bufferSize
    File(const string &fileName);
    void Release(const pos_type &pos);
    void Insert(Buffer *const buffer);
    bool Exist(const pos_type &pos);
    bool IsEnd(const pos_type &pos);
    size_t Convert(const pos_type &pos);
    Buffer *GetBuffer(const pos_type &pos, const pos_type &size);
    Buffer *GetBuffer(const pos_type &pos);
    pos_type GetOffset(const pos_type &pos, const pos_type &size = 0U);
    pos_type GetPos(const pos_type &pos);
public slots:
    void flush();
    void reset();
signals:
    //void flushed();
public:
    const pos_type &tellg();
    const pos_type &tellp();
    const pos_type &telle();
    bool eof();
    void seekg(const pos_type &pos);
    void seekp(const pos_type &pos);
    void resize(const pos_type &pos);
    template<typename T>
    auto get() -> const Valid<T> &;
    template<typename T>
    auto get(const pos_type &pos) -> const Valid<T> &;
    template<typename T>
    auto peek() -> const Valid<T> &;
    template<typename T, typename = Valid<T>>
    void unget();
    template<typename T, typename = Valid<T>>
    void put(const T& item);
    template<typename T, typename = Valid<T>>
    void put(const T& item, const pos_type &pos);
    template<typename T, typename = Valid<T>>
    File &operator>>(T &target);
    template<typename T, typename = Valid<T>>
    File &operator<<(const T &source);
    virtual ~File();
};

template<typename T, typename = File::Valid<T>>
File &File::operator<<(const T &source)
{
    put(source);
    return *this;
}

template<typename T, typename = File::Valid<T>>
File &File::operator>>(T &target)
{
    target = get<T>();
    return *this;
}

template<typename T, typename = File::Valid<T>>
void File::put(const T &item)
{
    put(item, WriteCursor);
    WriteCursor += sizeof(T);
}

template<typename T, typename = File::Valid<T>>
void File::put(const T &item, const pos_type &pos)
{
    Buffer *buff = GetBuffer(pos,sizeof(T));
    size_t offset = GetOffset(pos,sizeof(T));
    buff->Mutex.lock();
    buff->Dirty = true;
    memcpy(buff->Buff+ offset,(const char*)&item,sizeof(T));
    buff->Mutex.unlock();
}

template<typename T, typename = File::Valid<T>>
void File::unget()
{
    ReadCursor -= sizeof(T);
}

template<typename T>
auto File::peek() -> const Valid<T> &
{
    return get<T>(ReadCursor);
}

template<typename T>
auto File::get(const pos_type &pos) -> const Valid<T> &
{
    Buffer *buff = GetBuffer(pos,sizeof(T));
    size_t offset = GetOffset(pos,sizeof(T));
    return *(T*)(buff->Buff+ offset);
}

template<typename T>
auto File::get() -> const Valid<T> &
{
    ReadCursor += sizeof(T);
    return get<T>(ReadCursor - sizeof(T));
}

inline size_t File::Convert(const pos_type &pos)
{
    return pos / Buffer::bufferSize();
}

inline void File::reset()
{
    for(auto &i : Buffers)
        if(i.second->Dirty)
            delete i.second;
}

inline const File::pos_type &File::tellg()
{
    return ReadCursor;
}

inline const File::pos_type &File::tellp()
{
    return WriteCursor;
}

inline const File::pos_type &File::telle()
{
    return FileSize;
}


inline bool File::eof()
{
    return ReadCursor>=FileSize;
}

inline void File::seekg(const File::pos_type &pos)
{
    if(pos>=FileSize)
        ReadCursor = FileSize;
    else
        ReadCursor = pos;
}

inline void File::seekp(const File::pos_type &pos)
{
    if(pos>=FileSize)
        resize(pos);
    WriteCursor = pos;
}

inline void File::Release(const pos_type &pos)
{
    Buffers.erase(Convert(pos));
}

inline void File::Insert(Buffer * const buffer)
{
    Buffers.insert(std::make_pair(Convert(buffer->Position),buffer));
}

inline bool File::Exist(const pos_type &pos)
{
    return Buffers.find(Convert(pos)) != Buffers.end();
}

inline bool File::IsEnd(const pos_type &pos)
{
    return pos >= Stream.size();
}

#endif // FILE_H
