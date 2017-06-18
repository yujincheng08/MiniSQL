#ifndef MAIN_H
#define MAIN_H
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include "interpreter/Interpreter.h"
#include "bufferManager/BufferManager.h"
#include "api/API.h"
class Main : public QObject
{
    Q_OBJECT
    Interpreter *interpreter;
    BufferManager *bufferManager;
    API *api;
public:
    Main(QObject *parent = nullptr);

public slots:
    void run();

signals:
    void finished();
};

#endif // MAIN_H
