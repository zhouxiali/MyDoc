#ifndef VARIANT_H
#define VARIANT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Variant; }
QT_END_NAMESPACE

class Variant : public QWidget
{
    Q_OBJECT

public:
    Variant(QWidget *parent = nullptr);
    ~Variant();

private:
    Ui::Variant *ui;
};
#endif // VARIANT_H
