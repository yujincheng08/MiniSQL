#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include <QObject>
class BufferManager : QObject
{
    Q_OBJECT
private:
    const size_t blockSize;
    static size_t calBlockSize();
    static QString partition();
public:
    explicit BufferManager(QObject *parent = nullptr);
};
#endif
