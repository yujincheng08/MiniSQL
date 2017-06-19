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
    ~Main();
public slots:
    void run();

signals:
    void finished();
};


inline Main::Main(QObject *parent)
    :QObject(parent)
{
    interpreter = new Interpreter(this);
    api = new API(this);
    bufferManager = new BufferManager;
    connect(interpreter, SIGNAL(parsered(Action)), api, SLOT(execute(Action)));
    connect(api, SIGNAL(displayLine(string)), interpreter, SLOT(display(string)));
}

inline Main::~Main()
{
    delete interpreter;
    delete api;
    delete bufferManager;
}

inline void Main::run()
{

    interpreter->run();

    emit finished();
}

#endif // MAIN_H
