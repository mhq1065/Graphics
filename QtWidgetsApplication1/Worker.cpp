#include "Worker.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <Qpainter>

Worker::Worker(QObject* parent)
{
}

void Worker::drawImage()
{
	int x0 = 0, y0 = 0, x1 = 500, y1 = 500;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int p = (dx > dy ? dx : -dy) / 2, e2;
	for (;;) {
		QThread::msleep(200);
		emit outPix(x0, y0, Qt::red, 1);
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
