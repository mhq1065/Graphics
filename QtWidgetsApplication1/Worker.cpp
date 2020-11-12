#include "Worker.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <Qpainter>
#include <QMessageBox>
#include <cmath>
using namespace std;

int Rounding(const float a) { return int(a + 0.5); }
Worker::Worker(int width, int height, QObject* parent)
{
	this->width = width;
	this->height = height;
	this->t = 50;
	qDebug() << "init Worker progress" << '\n';
}

void Worker::dda(int p1_x, int p1_y, int p2_x, int p2_y)
{
	qDebug() << "dda" << '\n';

	int delta_x = abs(p1_x - p2_x);
	int delta_y = abs(p1_x - p2_y);
	int i = 0;
	float length = delta_x >= delta_y ? delta_x : delta_y;
	float dx = (p2_x - p1_x) / length;
	float dy = (p2_y - p1_y) / length;
	float x = p1_x;
	float y = p1_y;
	while (i <= length) {
		QThread::msleep(t);
		if (isOut(int(x + .5), int(y + .5))) {
			emit outMsg();
			break;
		}
		emit outPix(int(x + .5), int(y + .5), Qt::red, 1);
		y += dy;
		x += dx;
		i++;
	}
}

void Worker::bresenham(int p1_x, int p1_y, int p2_x, int p2_y)
{
	qDebug() << "bresenham" << '\n';

	int x0 = p1_x, y0 = p1_y, x1 = p2_x, y1 = p2_y;
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int p = (dx > dy ? dx : -dy) / 2, e2;
	for (;;) {
		QThread::msleep(t);
		if (isOut(x0, y0)) {
			emit outMsg();
			break;
		}
		qDebug() << x0 << 't' << y0 << '\n';
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

void Worker::oval(int x0, int y0, int rx, int ry)
{
	// 中心椭圆
	qDebug() << "oval" << '\n';
	// 绘制圆心
	emit outPix(x0, y0, Qt::black, 1);
	int a = rx, b = ry;
	int x, y;
	float d1, d2;
	x = 0;
	y = b;
	d1 = b * b + (double)a * a * (-b + 0.25);
	while ((double)b * b * (double(x) + 1) < (double)a * a * (y - 0.5)) {
		//qDebug() << x << y << endl;

		// 判断越界
		if (isOut(x + x0, y + y0) ||
			isOut(-x + x0, y + y0) ||
			isOut(-x + x0, y + y0) ||
			isOut(-x + x0, y + y0)) {
			emit outMsg();
			break;
		}
		emit outPix(x + x0, y + y0, Qt::red, 1);
		emit outPix(-x + x0, y + y0, Qt::red, 1);
		emit outPix(x + x0, -y + y0, Qt::red, 1);
		emit outPix(-x + x0, -y + y0, Qt::red, 1);
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
		//qDebug() << x << y << endl;
		// 判断越界
		if (isOut(x + x0, y + y0) ||
			isOut(-x + x0, y + y0) ||
			isOut(-x + x0, y + y0) ||
			isOut(-x + x0, y + y0)) {
			emit outMsg();
			break;
		}
		emit outPix(x + x0, y + y0, Qt::red, 1);
		emit outPix(-x + x0, y + y0, Qt::red, 1);
		emit outPix(x + x0, -y + y0, Qt::red, 1);
		emit outPix(-x + x0, -y + y0, Qt::red, 1);
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

void Worker::circle(int x, int y, int r)
{
	// bresenham circle
	qDebug() << "circle" << '\n';

	// 绘制圆心
	emit outPix(x, y, Qt::black, 1);

	int x0 = x, y0 = y;
	x = 0, y = r;
	int d = 1 - r;
	while (y >= x) {
		qDebug() << x << '\t' << y << '\t' << d << '\n';
		if (isOut(x0 + x, y + y0) ||
			isOut(x0 + y, x + y0) ||
			isOut(x0 - x, y + y0) ||
			isOut(x0 + y, -x + y0) ||
			isOut(x0 + x, -y + y0) ||
			isOut(x0 - y, +x + y0) ||
			isOut(x0 - x, -y + y0) ||
			isOut(x0 - y, -x + y0)) {
			emit outMsg();
			break;
		}
		emit outPix(x0 + x, y + y0, Qt::red, 1);
		emit outPix(x0 + y, x + y0, Qt::red, 1);
		emit outPix(x0 - x, y + y0, Qt::red, 1);
		emit outPix(x0 + y, -x + y0, Qt::red, 1);
		emit outPix(x0 + x, -y + y0, Qt::red, 1);
		emit outPix(x0 - y, +x + y0, Qt::red, 1);
		emit outPix(x0 - x, -y + y0, Qt::red, 1);
		emit outPix(x0 - y, -x + y0, Qt::red, 1);
		QThread::msleep(t);

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

bool Worker::isOut(int x, int y)
{
	if (x < -width / 2 ||
		x > width / 2 ||
		y > height / 2 ||
		y < -height)
	{
		return true;
	}
	return false;
}
