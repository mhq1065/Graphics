#include "canvas.h"
#include <Qpainter>
#include <QPixmap>
#include <QDebug>

canvas::canvas(QWidget* parent) :QWidget(parent)
{
	qDebug() << "init canvas" << '\n';
	// 设置中心位置
	center_x = 600;
	center_y = 360;
	Pix = QPixmap(center_x * 2, center_y * 2);
	Pix.fill(Qt::white);
}

void canvas::paintEvent(QPaintEvent*)
{
	QPainter Painter(this);
	Painter.drawPixmap(0, 0, center_x * 2, center_y * 2, Pix);
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
