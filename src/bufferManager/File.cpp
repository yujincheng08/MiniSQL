#include "File.h"
#include "BufferManager.h"
File::File(const QString &fileName)
    :FileName(fileName)
{
    Stream.rdbuf()->pubsetbuf(nullptr,0);
    Stream.open(FileName.toStdString(),std::ios_base::binary);
    Stream.seekg(Stream.end);
    BlockCount = ((BufferManager::blockSize() + Stream.tellg()) -1L)
            / BufferManager::blockSize();
    //while()
}
