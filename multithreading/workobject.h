#ifndef WORKOBJECT_H
#define WORKOBJECT_H
#include <QObject>
#include <QDebug>
#include <QtDBus/QtDBus>

class WorkObject : public QObject
{
    Q_OBJECT
public:
    WorkObject();
    ~WorkObject();
public:
    void run();
Q_SIGNALS:
    void Ipv4PathSignal(QString ipv4Path);
};

#endif // WORKOBJECT_H
