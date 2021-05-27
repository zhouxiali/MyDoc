#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList scaleList;
    scaleList<< tr("1min") << tr("5min") << tr("10min") << tr("30min") << tr("45min")
             <<tr("1hour") << tr("1.5hour") << tr("2hour") << tr("3hour") << tr("Never");
    Uslider * m_pSlider;
    m_pSlider = new Uslider(scaleList);
    m_pSlider->setStyleSheet( "QSlider::groove:horizontal {"
                                   "border: 0px none;"
                                   "background: palette(button);"
                                   "height: 8px;"
                                   "border-radius: 5px;"
                                   "}"

                                   "QSlider::handle:horizontal {"

                                   "height: 24px;"
                                   "width: 32px;"
                                   "margin: 30px;"
                                   "border-image: url(://img/plugins/mouse/slider.svg);"
                                   "margin: -8 -4px;"
                                   "}"

                                   "QSlider::add-page:horizontal {"
                                   "background: palette(button);"
                                   "border-radius: 20px;"
                                   "}"

                                   "QSlider::sub-page:horizontal {"
                                   "background: #2FB3E8;"
                                   "border-radius: 5px;"
                                   "}");
    m_pSlider->setRange(10,100);
    m_pSlider->setTickInterval(10);
    m_pSlider->setPageStep(10);
    m_pSlider->setTracking(false);
    m_pSlider->setSingleStep(10);
    m_pSlider->setMinimumWidth(495);
    m_pSlider->setTickPosition(QSlider::TicksBothSides);
    ui->verticalLayout_2->addWidget(m_pSlider);
}

Widget::~Widget()
{
    delete ui;
}

