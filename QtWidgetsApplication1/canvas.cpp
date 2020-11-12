#include "canvas.h"
#include <Qpainter>
#include <QPixmap>
#include <QDebug>

canvas::canvas(QWidget* parent) :QWidget(parent)
{
	qDebug() << "init canvas" << '\n';
	// 设置中心位置
	center_x = 300;
	center_y = 200;
	Pix = QPixmap(center_x * 2, center_y * 2);
	Pix.fill(Qt::white);
	draw_coordinate();
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
	emit outListMsg(x, y);
	this->update();
}


void canvas::draw_coordinate() {
	QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
	pen.setColor(QColor(0, 0, 0, 126));
	QPainter Painter(&Pix);
	Painter.setPen(pen);
	Painter.translate(center_x, center_y);
	Painter.scale(1, -1);
	Painter.drawLine(center_x, 0, -center_x, 0);
	Painter.drawLine(0,  center_y, 0, -center_y);
	this->update();
}