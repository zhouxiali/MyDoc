#include "variant.h"
#include "ui_variant.h"
#include <QDebug>
#include <QMap>
#include <QVariant>
#include <QColor>
Variant::Variant(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Variant)
{
    ui->setupUi(this);
    QStringList strList;
    strList.append("hello");
    strList.append("world");
    strList.append("!");
    QMap<QString,QVariant> map;
    map.insert("nice",12);
    map.insert("work","heihei");
    map.insert("真不错",QColor(124,124,124));
    map.insert("heihei",strList);
    QMapIterator<QString, QVariant> inter(map);
    while (inter.hasNext()) {
        inter.next();
        if (inter.value().type() == QVariant::StringList) {
            QString str = QString("%1").arg(inter.key());
            qDebug()<< "key:" <<str;
            QStringList myList = map[str].toStringList();
            for(int m = 0; m < myList.size(); m ++) {
                qDebug()<<myList.at(m);
            }
        } else {
            qDebug()<< inter.key() << ":" << inter.value();
        }
    }
}

Variant::~Variant()
{
    delete ui;
}

