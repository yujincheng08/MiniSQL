#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>

class Interpreter : public QObject
{
    Q_OBJECT
public:
    explicit Interpreter(QObject *parent = 0);

signals:

public slots:
};

#endif // INTERPRETER_H