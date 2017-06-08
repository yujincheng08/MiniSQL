#include "File.h"
#include "BufferManager.h"
#include <QCoreApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc,argv);
    File &file = BufferManager::open("xxx");
    //std::ios::sync_with_stdio(false);
    int s = file.get<int>(900000*4);
    for(int i=0;i<100000;++i)
        std::cout<<s<<std::endl;
    return a.exec();
}
