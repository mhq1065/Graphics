#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();

    //w.paintbre();
    return a.exec();
}
