#pragma once

#include "ui_QtWidgetsApplication1.h"
#include "Worker.h"

#include <QtWidgets/QMainWindow>
#include <Qpainter>
#include <qtimer.h>

#include <QThread>

class QtWidgetsApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsApplication1(QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);

public slots:
	void paintbre();
	//void slot1();
	void slot1(int x, int y);
	void draw_point(int x, int y, QColor c, int w);
private:
	Ui::QtWidgetsApplication1Class ui;
	QPixmap Pix;
	//QTimer* timer;

	QThread* m_thread;
	Worker* worker;
};
