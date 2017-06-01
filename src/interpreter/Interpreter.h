#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
class Scanner;
class Interpreter : public QObject
{
    Q_OBJECT
    void *parser;
    Scanner *scanner;
public:
    explicit Interpreter(QObject *parent = 0);
signals:

public slots:
    void run();
};

#endif // INTERPRETER_H
