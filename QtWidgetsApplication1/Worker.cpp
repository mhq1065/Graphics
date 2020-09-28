#include "Worker.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <Qpainter>

#include <cmath>

int Rounding(const float a) { return int(a + 0.5); }
Worker::Worker(QObject* parent)
{
}

void Worker::dda()
{
	int x0 = 0, y0 = 0, x1 = -100, y1 = 500;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int p = (dx > dy ? dx : -dy) / 2, e2;
	for (;;) {
		QThread::msleep(100);
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

void Worker::bresenham()
{
	int x0 = 0, y0 = 0, x1 = -100, y1 = 500;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int p = (dx > dy ? dx : -dy) / 2, e2;
	for (;;) {
		QThread::msleep(100);
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

void Worker::oval()
{
	// ÖÐÐÄÍÖÔ²
	int x0 = 0, y0 = 0;

	int Rx = 100, Ry = 50;
	int Rx2 = Rx * Rx, Ry2 = Ry * Ry;
	int p;
	int x = 0, y = Ry;
	int px = 0, py = 2 * Rx2 * y;
	p = Rounding(Ry2 - Rx2 * Ry + Rx2 / 4);
	emit outPix(x, y, Qt::black, 1);
	emit outPix(-x, y, Qt::red, 1);
	emit outPix(x, -y, Qt::red, 1);
	emit outPix(-x, -y, Qt::red, 1);
	while (Ry2*x < Rx2*y) {
		x++;
		px += 2 * Ry2;
		if (p < 0) {
			p += Ry2 + px;
		}
		else {
			y--;
			py -= 2 * Rx2;
			p += Ry2 + px - py;
		}
		QThread::msleep(100);

		emit outPix(x, y, Qt::black, 1);
		emit outPix(-x, y, Qt::red, 1);
		emit outPix(x, -y, Qt::red, 1);
		emit outPix(-x, -y, Qt::red, 1);
	}
	p = Rounding(Ry2 * (x + 0.5) * (x + 0.5) + (long int)Rx2 * (y - 1) * (y - 1) - Rx2 *  (long int)Rx2);
	while (y > 0) {
		y--;
		py -= 2 * Rx2;
		if (p > 0)
		{
			p += Rx2 - py;
		}
		else {
			x++;
			px += 2 * Rx2;
			p += Rx2 - py + px;
		}
		QThread::msleep(100);

		emit outPix(x, y, Qt::red, 1);
		emit outPix(-x, y, Qt::red, 1);
		emit outPix(x, -y, Qt::red, 1);
		emit outPix(-x, -y, Qt::red, 1);
	}
}
