#include "variant.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Variant w;
    w.show();
    return a.exec();
}
