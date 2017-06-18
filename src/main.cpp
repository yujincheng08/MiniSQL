#include <ios>
#include "main.h"

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    QCoreApplication a(argc, argv);
    Main *m = new Main(&a);
    QObject::connect(m, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, m, SLOT(run()));
    return a.exec();
}

Main::Main(QObject *parent)
    :QObject(parent)
{
    interpreter = new Interpreter(this);
    api = new API(this);
}

void Main::run()
{
    interpreter->run();
    connect(interpreter, &Interpreter::parsered, api, &API::execute);
    connect(api, SIGNAL(displayLine(std::string)), interpreter, SLOT(display(std::string)));
    emit finished();
}
