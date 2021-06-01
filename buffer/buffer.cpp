#include "buffer.h"
#include "ui_buffer.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QByteArray array;
    QBuffer buffer(&array);
    write_buffer(0, buffer);
    read_buffer(buffer);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::write_buffer(int type, QBuffer& buffer)   //写入缓冲区方法
{
    //以只写方式打开缓冲区
    if( buffer.open(QIODevice::WriteOnly) ) {
        QDataStream out(&buffer);
        out << type;
        //写入数据
        if (type == 0) {
            out << QString("badogyang software");
            out << 3.14159;
        } else if(type == 1) {
            out << 3;
            out << 1314;
        } else if(type == 2) {
            out << 531.135;
        }
        //关闭缓冲区
        buffer.close();
    }
}

void Widget::read_buffer(QBuffer& buffer)
{
    if (buffer.open(QIODevice::ReadOnly)) {
        int type = -1;
        QDataStream in(&buffer);
        in >> type;
        qDebug()<<"type"<<type;
        if (type == 0) {
            QString s = "";
            double value = 0;
            in >> s;
            in >> value;
            qDebug() << s;
            qDebug() << value;
        } else if (type == 1) {
            int a;
            int b;
            in >> a;
            in >> b;
            qDebug() << a;
            qDebug() << b;
        } else if (type == 2) {
            double value = 0;
            in >> value;
            qDebug() << value;
        }
        buffer.close();
    }
}


