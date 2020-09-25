#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
    void paintEvent(QPaintEvent*);
    void draw_point(int const x, int const y, QColor const c, int const w);

public slots:
    void paintbre();
    void slot1();
private:
    Ui::QtWidgetsApplication1Class ui;
    QPixmap Pix;
};
