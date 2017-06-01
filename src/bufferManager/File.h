#ifndef FILE_H
#define FILE_H

#include <QString>
#include <fstream>

class File
{
    QString FileName;
    size_t BlockCount;
    std::fstream Stream;
public:
    File(QString fileName);
};

#endif // FILE_H
