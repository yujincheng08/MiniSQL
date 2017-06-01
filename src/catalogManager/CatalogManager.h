#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <QObject>

class catalogManager : public QObject
{
    Q_OBJECT
public:
    explicit catalogManager(QObject *parent = 0);

signals:

public slots:
};

#endif // CATALOGMANAGER_H