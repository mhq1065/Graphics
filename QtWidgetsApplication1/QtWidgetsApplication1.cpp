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

	worker = new Worker;
	m_thread = new QThread;
	worker->moveToThread(m_thread);
	m_thread->start();

	Pix = QPixmap(400, 300);
	Pix.fill(Qt::white);
	connect(ui.actionbreshen, SIGNAL(triggered()), worker, SLOT(drawImage()), Qt::QueuedConnection);
	connect(ui.actionDDa, SIGNAL(triggered()), this, SLOT(paintbre()));
	connect(worker, SIGNAL(outPix(int, int, QColor, int)), this, SLOT(draw_point(int, int, QColor, int)), Qt::QueuedConnection);
	m_thread->start();
}
void QtWidgetsApplication1::paintEvent(QPaintEvent*) {
	QPainter Painter(this);
	//QPainter Painter(this);
	Painter.drawPixmap(0, 0, 400, 300, Pix);
}
void QtWidgetsApplication1::draw_point(int  x, int  y, QColor  c, int  w) {
	qDebug() << x << y << '\n';
	QPainter Painter(&Pix);
	Painter.setPen(QPen(c, w));
	Painter.translate(150, 100);
	Painter.scale(1, -1);
	Painter.drawPoint(x, y);
	this->update();
}

void QtWidgetsApplication1::paintbre() {
	qDebug() << "Receives Newspaper: ";

	int x0 = 0, y0 = 0, x1 = 500, y1 = 500;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int p = (dx > dy ? dx : -dy) / 2, e2;
	for (;;) {
		this->draw_point(x0, y0, Qt::black, 1);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = p;
		if (e2 > -dx) {
			p -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			p += dx;
			y0 += sy;
		}
	}
	this->update();
}

//void QtWidgetsApplication1::slot1() {
//	//QWidget* new_w = new QWidget();
//	//new_w->show();
//	qDebug() << "test" << '\n';
//}
void QtWidgetsApplication1::slot1(int x, int y) {
	//QWidget* new_w = new QWidget();
	//new_w->show();
	qDebug() << "test" << '\n';
}