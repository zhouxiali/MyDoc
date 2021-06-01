#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QBuffer>
#include "workobject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void readInfo();
private:
    QThread     * mThread;
    WorkObject  * mWorkObject;
    QString       mIpv4Path;
    QBuffer       buffer;
};
#endif // WIDGET_H
