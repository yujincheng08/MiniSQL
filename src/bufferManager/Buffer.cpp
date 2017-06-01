#include "Buffer.h"
#include <QDir>
#include <QString>
namespace windows
{
#include <windows.h>
}

size_t Buffer::BlockSize = Buffer::calBlockSize();
size_t Buffer::calBlockSize()
{
    windows::DWORD SectorsPerCluster,lpBytesPerSector;
    windows::GetDiskFreeSpace(partition().toStdWString().c_str(),
                         &SectorsPerCluster,&lpBytesPerSector,nullptr,nullptr);
    return static_cast<size_t>(SectorsPerCluster*lpBytesPerSector);
}

QString Buffer::partition()
{
    QDir current = QDir::current();
    while(current.cdUp());
    return current.absolutePath();
}
