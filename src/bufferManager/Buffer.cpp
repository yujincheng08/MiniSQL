#include "Buffer.h"
#include <QDir>
#include <QString>
namespace windows
{
#include <windows.h>
}

static QString partition()
{
    QDir current = QDir::current();
    while(current.cdUp());
    return current.absolutePath();
}

static size_t calBufferSize()
{
    windows::DWORD SectorsPerCluster,lpBytesPerSector;
    windows::GetDiskFreeSpace(partition().toStdWString().c_str(),
                         &SectorsPerCluster,&lpBytesPerSector,nullptr,nullptr);
    return static_cast<size_t>(SectorsPerCluster*lpBytesPerSector);
}


const size_t Buffer::BufferSize = calBufferSize();

