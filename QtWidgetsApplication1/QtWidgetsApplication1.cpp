#include "QtWidgetsApplication1.h"
#include <Qpainter>
#include <QPixmap>
#include <iostream>
#include <QDebug>
// https://blog.csdn.net/sigmarising/article/details/79920380
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Pix = QPixmap(size());
	Pix.fill(Qt::white);
	connect(ui.actionbreshen, SIGNAL(triggered()), this, SLOT(paintbre()));
	connect(ui.actionDDa, SIGNAL(triggered()), this, SLOT(slot1()));
}
void QtWidgetsApplication1::paintEvent(QPaintEvent*) {
	QPainter Painter(ui.graphicsView->viewport());
	//QPainter Painter(this);
	Painter.drawPixmap(0, 0, 300, 200, Pix);
}
void QtWidgetsApplication1::draw_point(int const x, int const y, QColor const c, int const w) {
	QPainter Painter(&Pix);
	Painter.setPen(QPen(c, w));
	Painter.drawPoint(x, y);
}

void QtWidgetsApplication1::paintbre() {
	qDebug() << "Receives Newspaper: ";

	int x0 = 0, y0 = 0, x1 = 200, y1 = 200;
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
}

void QtWidgetsApplication1::slot1() {
	QWidget* new_w = new QWidget();
	new_w->show();
}