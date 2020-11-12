#pragma once

#include "ui_QtWidgetsApplication1.h"
#include "Worker.h"

#include <QtWidgets/QMainWindow>
#include <Qpainter>
#include <qtimer.h>

#include <QMessageBox>
#include <QThread>
#include <QString>

class QtWidgetsApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsApplication1(QWidget* parent = Q_NULLPTR);
	void paintEvent(QPaintEvent*);
	//bool eventFilter(QObject* watched, QEvent* event);


public slots:
	void slot1();
	void CircleController();
	void OvalController();
	void DdaController();
	void BresenhamController();
	void showMsg();
	void showListMsg(int,int);
signals:
	void Circle_signal(int x, int y, int r);
signals:
	void Oval_signal(int x, int y, int rx, int ry);
signals:
	void Bresenham_signal(int, int, int, int);
signals:
	void Dda_signal(int, int, int, int);

private:
	Ui::QtWidgetsApplication1Class ui;
	QPixmap Pix;
	//QTimer* timer;
	QMessageBox msgBox{ QString::fromLocal8Bit("¾¯¸æ"),
		QString::fromLocal8Bit("TanÇúÏß"),
		QMessageBox::Critical,
		QMessageBox::Ok | QMessageBox::Default,
		QMessageBox::Cancel | QMessageBox::Escape,
		0 };
	QThread* m_thread;
	Worker* worker;
};
