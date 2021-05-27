#include "slider.h"

#include <QStyle>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QDebug>


Uslider::Uslider(QStringList list) : scaleList(list), QSlider(Qt::Horizontal)
{
    this->setMinimumHeight(50);
    this->setMaximumHeight(100);
    QString locale = QLocale::system().name();
    if ("zh_CN" == locale) {
        laungeBool = true;
    } else if ("en_US" == locale) {
        laungeBool = false;
    }

}

void Uslider::wheelEvent(QWheelEvent *e)
{
    static int touchMoveDistance = 0;
    int oldValue = value();
    int newValue = 0;

    int maxTouchPadMoveMinToMaxDistance = TOTAL_DELTA;
    int totalStep = (maximum() - minimum()) / pageStep();

    int step = pageStep();

    touchMoveDistance += e->delta();

    if(touchMoveDistance > (maxTouchPadMoveMinToMaxDistance / totalStep)){
        newValue = oldValue + step;
        touchMoveDistance = 0;
    }
    else if(touchMoveDistance < (maxTouchPadMoveMinToMaxDistance / totalStep)*-1){
        newValue = oldValue - step;
        touchMoveDistance = 0;
    }
    else{
        goto END;
    }

    newValue = newValue > maximum()? maximum():newValue;
    newValue = newValue < minimum()? minimum():newValue;

    setValue(newValue);
END:
    e->accept();
}

void Uslider::mousePressEvent(QMouseEvent * event) {
    if (event->button() != Qt::LeftButton)
        return;
    setSliderDown(true);
}

static bool bIsMove = false;
void Uslider::mouseMoveEvent(QMouseEvent * event) {
    bIsMove = true;
    int32_t pos = MousePostionToSliderVal(event->pos());
    if (pos != sliderPosition()) {
        setSliderPosition(pos);
        float endPos = pos;
        endPos = round(endPos / 10);
        emit sliderMoved(endPos * 10);
    }
}

void Uslider::mouseReleaseEvent(QMouseEvent * event) {
    setSliderDown(true);
    if (!isEnabled() || event->button() != Qt::LeftButton) {
        bIsMove = false;
        return;
    }

    if (bIsMove) {
        QSlider::mouseReleaseEvent(event);
        bIsMove = false;
    } else {
        int32_t pos = MousePostionToSliderVal(event->pos());
        if (pos != sliderPosition()) {
            setSliderPosition(pos);
            float endPos = pos;
            endPos = round(endPos / 10);
            emit sliderMoved(endPos * 10);
        }
    }
}

int32_t Uslider::MousePostionToSliderVal(const QPoint & pos) {
    int32_t duration = maximum() - minimum();
    int32_t sliderPos = 0;
    qreal mousePos = 0;
    uint16_t hanleLen = 0;
    if (Qt::Vertical == orientation()) {
        //设置了handle高度  则以m_handleLen为准， 如无设置 则以宽度一半为handleLen
        hanleLen = m_handleLen ? m_handleLen : width() / 2.0;
        mousePos = (qreal)(pos.y() - hanleLen / 2);
        if (0 > mousePos)
            mousePos = 0;
        else if (mousePos > height() - hanleLen)
            mousePos = (qreal)(height() - hanleLen);
        sliderPos = maximum() - duration * (mousePos / (height() - hanleLen));
    } else {
        //设置了handle宽度  则以m_handleLen为准， 如无设置 则以高度度一半为handleLen
        hanleLen = m_handleLen ? m_handleLen : height() / 2.0;
        mousePos = (qreal)(pos.x() - hanleLen / 2);
        if (0 > mousePos)
            mousePos = 0;
        else if (mousePos > width() - hanleLen)
            mousePos = (qreal)(width() - hanleLen);
        sliderPos = minimum() + duration * (mousePos / (width() - hanleLen));
    }
    float endPos = sliderPos;
    endPos = round(endPos / 10) * 10;
    return endPos;
}

void Uslider::paintEvent(QPaintEvent *e)
{

    QSlider::paintEvent(e);

    auto painter = new QPainter(this);
//    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(QPalette::Text));

    auto rect = this->geometry();

    int numTicks = (maximum() - minimum())/tickInterval();

    QFontMetrics fontMetrics = QFontMetrics(this->font());

    if (this->orientation() == Qt::Horizontal) {
        int fontHeight = fontMetrics.height();

        for (int i=0; i<=numTicks; i++) {
            int tickNum = minimum() + (tickInterval() * i);
            int tickX = 0;
            int tickY = 0;
            if( 0 == i) {
                tickX = 0;
            } else if (numTicks == i){
                if (laungeBool) {
                    //tickX = rect.width()-33;
                    QRect rec = fontMetrics.boundingRect(this->scaleList.at(numTicks));
                    tickX = rect.width()-rec.width() - 2;
                } else {
                    QRect rec = fontMetrics.boundingRect(this->scaleList.at(numTicks));
                    tickX = rect.width()-rec.width() - 2;
                }
            }else{
                QRect rec = fontMetrics.boundingRect(this->scaleList.at(i));
                tickX = (((rect.width()/numTicks) * i) - (rec.width()/2) + 6);
            }
            tickY = rect.height()/2 + fontHeight + 1;
            painter->drawText(QPoint(tickX, tickY),
                                 this->scaleList.at(i));
        }
    }
    painter->end();
}


