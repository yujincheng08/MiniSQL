#include "File.h"
#include "BufferManager.h"

File::File(const string &fileName)
    :Stream(fileName.c_str()),FileSize(Stream.size())
{
    Stream.open(QFile::ReadWrite|QFile::Unbuffered);
    BlockCount = Convert(FileSize);
}

Buffer *File::GetBuffer(const pos_type &pos)
{
    auto i = Buffers.find(Convert(pos));
    if(i==Buffers.end())
    {
        Buffer * buffer = BufferManager::bufferManager().buff(this,GetPos(pos));
        BufferManager::bufferManager().preRead(this, (size_t)pos + Buffer::bufferSize());
        return buffer;
    }
    else
        return i->second;
}

Buffer *File::GetBuffer(const pos_type &pos, const pos_type &size)
{
    Buffer *buffer;
    auto newpos = pos+size;
    auto newBlock = Convert(newpos);
    auto offset = GetOffset(pos,size) + size;
    if(newBlock>BlockCount)
    {
        resize(newBlock * Buffer::bufferSize() + offset);
        buffer = BufferManager::bufferManager().buff(this,GetPos(newpos), offset);
    }
    else
    {
        buffer = GetBuffer(newpos);
        if(buffer->Size < offset)
            resize(newBlock * Buffer::bufferSize() + offset);
    }
    return buffer;
}

File::pos_type File::GetOffset(const pos_type &pos, const pos_type &size)
{
    pos_type offset = (pos + size) % Buffer::bufferSize();
    if(offset < size)
        return 0U;
    else
        return offset - size;
}

File::pos_type File::GetPos(const File::pos_type &pos)
{
    return Convert(pos) * Buffer::bufferSize();
}

File::~File()
{
    BufferManager::bufferManager().wait();
    for(auto &i : Buffers)
        delete i.second;
    Stream.close();
}

void File::resize(const pos_type &pos)
{
    size_t oldBlock = Convert(FileSize);
    size_t newBlock = Convert(pos);
    if(newBlock<oldBlock)
    {
        for(;newBlock<=oldBlock;++newBlock)
        {
            auto i = Buffers.find(newBlock);
            if(i!=Buffers.end())
            {
                delete i->second;
                Buffers.erase(i);
            }
        }
    }
    else
    {
        auto i = Buffers.find(oldBlock);
        if(i!=Buffers.end())
        {
            if(newBlock==oldBlock)
                i->second->changeSize(pos % Buffer::bufferSize());
            else
                i->second->changeSize(Buffer::bufferSize());
        }
    }
    FileSize = pos;
}


void File::flush()
{
    for(auto i : Buffers)
        if(i.second->Dirty)
            BufferManager::bufferManager().queueBuff(i.second);
}
