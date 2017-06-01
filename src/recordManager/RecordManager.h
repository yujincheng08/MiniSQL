#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <QObject>

class RecordManager : public QObject
{
    Q_OBJECT
public:
    explicit RecordManager(QObject *parent = 0);

signals:

public slots:
};

#endif // RECORDMANAGER_H