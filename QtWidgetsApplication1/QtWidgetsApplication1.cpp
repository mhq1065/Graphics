#include "QtWidgetsApplication1.h"

#include <Qpainter>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include <Qtimer>

// https://blog.csdn.net/sigmarising/article/details/79920380
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// 新建线程处理画图以及延时
	worker = new Worker;
	m_thread = new QThread;
	worker->moveToThread(m_thread);
	m_thread->start();
	// 初始化
	Pix = QPixmap(400, 300);
	Pix.fill(Qt::white);
	// 请求画图
	connect(ui.actionbreshen, SIGNAL(triggered()), worker, SLOT(bresenham()));
	connect(ui.actionDDa, SIGNAL(triggered()), worker, SLOT(dda()));
	connect(ui.actionoval, SIGNAL(triggered()), worker, SLOT(oval()));
	// 接收画点信号
	connect(worker, SIGNAL(outPix(int, int, QColor, int)), this, SLOT(draw_point(int, int, QColor, int)), Qt::QueuedConnection);
	// 开始线程
	m_thread->start();
}
void QtWidgetsApplication1::paintEvent(QPaintEvent*) {
	QPainter Painter(this);
	Painter.drawPixmap(0, 0, 400, 300, Pix);
}
void QtWidgetsApplication1::draw_point(int  x, int  y, QColor  c, int  w) {
	qDebug() << x << y << '\n';
	QPainter Painter(&Pix);
	Painter.setPen(QPen(c, w));
	Painter.translate(200, 200);
	Painter.scale(1, -1);
	Painter.drawPoint(x, y);
	this->update();
}