#ifndef USLIDER_H
#define USLIDER_H

#include <QSlider>
#include <QPaintEvent>
#include <QWidget>
#include <QStringList>
#include <QtMath>
class Uslider : public QSlider
{

public:
    QStringList scaleList;
public:
    Uslider(QStringList list);
    void paintEvent(QPaintEvent *ev);
    bool laungeBool;
private:
    const int TOTAL_DELTA = 1200;
    uint16_t m_handleLen = 25;
protected:
    //鼠标按下
    virtual void mousePressEvent(QMouseEvent * event);
    //鼠标拖动
    virtual void mouseMoveEvent(QMouseEvent * event);
    //鼠标松开
    virtual void mouseReleaseEvent(QMouseEvent * event);

private:
    int32_t MousePostionToSliderVal(const QPoint & pos);
protected:
     void wheelEvent(QWheelEvent *e);
};

#endif // USLIDER_H

