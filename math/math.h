#ifndef MATH_H
#define MATH_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class math; }
QT_END_NAMESPACE

class math : public QWidget
{
    Q_OBJECT

public:
    math(QWidget *parent = nullptr);
    ~math();

private:
    Ui::math *ui;
    void MAP();
    void VECTOR();
};
#endif // MATH_H
