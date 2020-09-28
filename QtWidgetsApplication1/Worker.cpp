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
	

	int a = 20, b = 10;
	int x, y;
	unsigned long int t = 50;
	float d1, d2;
	x = 0;
	y = b;
	d1 = b * b + (double)a * a * (-b + 0.25);
	while ((double)b * b * (double(x) + 1) < (double)a * a * (y - 0.5)) {
		qDebug() << x << y << endl;
		emit outPix(x, y, Qt::red, 1);
		emit outPix(-x, y, Qt::red, 1);
		emit outPix(x, -y, Qt::red, 1);
		emit outPix(-x, -y, Qt::red, 1);
		QThread::msleep(t);

		if (d1 < 0) {
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else {
			d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			x++;
			y--;
		}
	}
	d2 = pow(b * (x + 0.5), 2) + pow(a * (y - 1), 2) - pow(a * b, 2);
	while (y >= 0) {
		qDebug() << x << y << endl;
		emit outPix(x, y, Qt::red, 1);
		emit outPix(-x, y, Qt::red, 1);
		emit outPix(x, -y, Qt::red, 1);
		emit outPix(-x, -y, Qt::red, 1);
		QThread::msleep(t);

		if (d2 < 0) {
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;
		}
		else {
			d2 += a * a * (-2 * y + 3);
			y--;
		}
	}
}

void Worker::circle()
{
	// bresenham circle
	int R = 101;
	int x0 = 1, y0 = 1;
	int x = 0, y = R;
	int d = 1 - R;
	while (y >= x) {
		emit outPix(x0 + x, y + y0, Qt::red, 1);
		emit outPix(x0 + y, x + y0, Qt::red, 1);
		emit outPix(x0 - x, y + y0, Qt::red, 1);
		emit outPix(x0 + y, -x + y0, Qt::red, 1);
		emit outPix(x0 + x, -y + y0, Qt::red, 1);
		emit outPix(x0 - y, +x + y0, Qt::red, 1);
		emit outPix(x0 - x, -y + y0, Qt::red, 1);
		emit outPix(x0 - y, -x + y0, Qt::red, 1);
		QThread::msleep(50);

		if (d < 0) {
			d += 2 * x + 3;
		}
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
