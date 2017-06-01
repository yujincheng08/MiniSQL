#include "BufferManager.h"
#include <QDir>
namespace windows
{
#include <windows.h>
}
size_t BufferManager::calBlockSize()
{
    windows::DWORD SectorsPerCluster,lpBytesPerSector;
    windows::GetDiskFreeSpace(partition().toStdWString().c_str(),
                         &SectorsPerCluster,&lpBytesPerSector,nullptr,nullptr);
    return static_cast<size_t>(SectorsPerCluster*lpBytesPerSector);
}

QString BufferManager::partition()
{
    QDir current = QDir::current();
    while(current.cdUp());
    return current.absolutePath();
}

BufferManager::BufferManager(QObject *parent)
    :QObject(parent),blockSize(calBlockSize())
{

}
