#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mThread = new QThread;
    mWorkObject = new WorkObject;
    mWorkObject->moveToThread(mThread);
    connect(mThread, &QThread::started, mWorkObject, &WorkObject::run);
    connect(mWorkObject, &WorkObject::Ipv4PathSignal, this, [=] (QString ipv4Path) {
        qDebug()<<ipv4Path;
        if( buffer.open(QIODevice::WriteOnly) ) {
            QDataStream out(&buffer);
            out << ipv4Path;
            //关闭缓冲区
            buffer.close();
        }
        readInfo();
        mThread->quit(); //退出事件循环
        mThread->wait(); //释放资源
    });
    connect(mThread, &QThread::finished, mWorkObject, &WorkObject::deleteLater);
    connect(mWorkObject, &WorkObject::destroyed, mThread, &QThread::deleteLater);
    mThread->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readInfo()
{
    if (buffer.open(QIODevice::ReadOnly)) {
        QDataStream in(&buffer);
        in >> mIpv4Path;
        qDebug()<<"mIpv4Path"<<mIpv4Path;
        buffer.close();
    }
}
