#include "math.h"
#include "ui_math.h"
#include <QMap>
#include<QVector>

#include <QDebug>
struct myStruct
{
    int count1;
    QString name;
};

struct  myTemplate
{
    QString str;
    myStruct myStr;
};
math::math(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::math)
{
    ui->setupUi(this);
    MAP();
    VECTOR();

    myStruct str ;
    str.count1 = 122;
    str.name = "zhouxiali";
    qDebug()<<str.name;

    myTemplate tem;
    tem.myStr.count1 = 23;
    tem.myStr.name = "周夏立";
    qDebug()<<tem.myStr.count1;
    qDebug()<<tem.myStr.name;
}

math::~math()
{
    delete ui;
}

void math::MAP() {
    QMap<QString,int> map;
    map.insert("zhouxiali",123123);
    map.insert("sichengxin",222);
    map.insert("xinxin",231);

    qDebug()<<map.value("xinxin");
    //遍历方式一
    QMapIterator<QString,int> iter(map);
    while(iter.hasNext())
    {
        iter.next();  ///放在前面
        qDebug()<<iter.key()<<" "<<iter.value();
    }
    //遍历方式二
    QMap<QString,int>::ConstIterator i = map.constBegin();
    while(i!=map.constEnd())
    {
        qDebug()<<i.key()<<": "<<i.value();
        ++i;
    }

    //不改变顺序改变value
    QMap<QString,int>::Iterator it;
    it=map.find("xinxin");
    if(it!=map.end())
        it.value()=8;
    for(QMap<QString,int>::ConstIterator ite=map.constBegin(); ite!=map.constEnd(); ++ite)
        qDebug()<<ite.key()<<": "<<ite.value();
}

void math::VECTOR() {
    QVector<QString> strArray;
    strArray.append("zhouxiali");
    strArray << "xinxin";
    strArray.replace(1,"sichengxin");
    QVector<QString>::iterator ite;
    for(ite = strArray.begin(); ite != strArray.end(); ite ++) {
        qDebug()<< *ite << "\0";
    }
}
