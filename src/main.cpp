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

