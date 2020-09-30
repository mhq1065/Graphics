#include "canvas.h"
#include <Qpainter>
#include <QPixmap>
#include <QDebug>

canvas::canvas(QWidget* parent) :QWidget(parent)
{
	qDebug() << "init canvas" << '\n';
	// 设置中心位置
	center_x = 250;
	center_y = 200;
	Pix = QPixmap(600, 600);
	Pix.fill(Qt::white);
}

void canvas::paintEvent(QPaintEvent*)
{
	QPainter Painter(this);
	Painter.drawPixmap(0, 0, 600, 600, Pix);
}

void canvas::draw_point(int x, int y, QColor c, int w)
{
	QPainter Painter(&Pix);
	Painter.setPen(QPen(c, w));
	Painter.translate(center_x, center_y);
	Painter.scale(1, -1);
	Painter.drawPoint(x, y);
	this->update();
}
