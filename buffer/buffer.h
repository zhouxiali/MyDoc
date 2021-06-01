#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBuffer>
#include <QDebug>

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
    void write_buffer(int type, QBuffer& buffer);
    void read_buffer(QBuffer& buffer);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
