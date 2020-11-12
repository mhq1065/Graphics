#include "QtWidgetsApplication1.h"
#include "canvas.h"
#include <Qpainter>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include <Qtimer>
#include <QColorDialog>
#include <QMessageBox>
#include <QString>

// https://blog.csdn.net/sigmarising/article/details/79920380
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	int height = 400, width = 600;
	ui.setupUi(this);
	// 新建线程处理画图以及延时
	worker = new Worker(width, height);
	m_thread = new QThread;
	worker->moveToThread(m_thread);
	m_thread->start();
	// 请求画图
	connect(this, SIGNAL(Circle_signal(int, int, int)), worker, SLOT(circle(int, int, int)));
	connect(this, SIGNAL(Oval_signal(int, int, int, int)), worker, SLOT(oval(int, int, int, int)));
	connect(this, SIGNAL(Dda_signal(int, int, int, int)), worker, SLOT(dda(int, int, int, int)));
	connect(this, SIGNAL(Bresenham_signal(int, int, int, int)), worker, SLOT(bresenham(int, int, int, int)));
	// 接收画点信号
	connect(worker, SIGNAL(outPix(int, int, QColor, int)), ui.widget, SLOT(draw_point(int, int, QColor, int)));
	// 接受越界信号
	connect(worker, SIGNAL(outMsg()), this, SLOT(showMsg()));
	// 接受item信号
	connect(ui.widget, SIGNAL(outListMsg(int, int)), this, SLOT(showListMsg(int, int)));
	// 开始线程
	m_thread->start();
	// 强制规定画框大小
	ui.widget->resize(QSize(width, height));
}
void QtWidgetsApplication1::paintEvent(QPaintEvent*) {
	QPainter Painter(this);
	Painter.drawPixmap(0, 20, 700, 720, Pix);
}

void QtWidgetsApplication1::slot1()
{
	qDebug() << "hello" << '\n';
}

void QtWidgetsApplication1::CircleController()
{
	int x = ui.circle_x->text().toInt();
	int y = ui.circle_y->text().toInt();
	int r = ui.circle_r->text().toInt();
	qDebug() << x << y << r << '\n';
	emit Circle_signal(x, y, r);
}

void QtWidgetsApplication1::OvalController()
{
	int x = ui.oval_x->text().toInt();
	int y = ui.oval_y->text().toInt();
	int rx = ui.oval_r_x->text().toInt();
	int ry = ui.oval_r_y->text().toInt();
	qDebug() << x << y << rx << ry << '\n';
	emit Oval_signal(x, y, rx, ry);
}

void QtWidgetsApplication1::DdaController()
{
	int p1_x = ui.dda_p1_x->text().toInt();
	int p1_y = ui.dda_p1_y->text().toInt();
	int p2_x = ui.dda_p2_x->text().toInt();
	int p2_y = ui.dda_p2_y->text().toInt();
	emit Dda_signal(p1_x, p1_y, p2_x, p2_y);
}

void QtWidgetsApplication1::BresenhamController()
{
	int p1_x = ui.bresenham_p1_x->text().toInt();
	int p1_y = ui.bresenham_p1_y->text().toInt();
	int p2_x = ui.bresenham_p2_x->text().toInt();
	int p2_y = ui.bresenham_p2_y->text().toInt();
	emit Bresenham_signal(p1_x, p1_y, p2_x, p2_y);
}

void QtWidgetsApplication1::showMsg()
{
	msgBox.show();
}

void QtWidgetsApplication1::showListMsg(int x, int y)
{
	QListWidgetItem* item = new QListWidgetItem;
	QString str = tr(",");
	str = "(" + QString::number(x) + "," + QString::number(y) + ")";

	item->setText(str);
	ui.MsgList->addItem(item);
}
