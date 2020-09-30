#pragma once
#include <QWidget>
#include <Qpainter>
#include <QPixmap>

class canvas:public QWidget
{
	Q_OBJECT
public:
	canvas(QWidget* parent = Q_NULLPTR);
public slots:
	void draw_point(int x, int y, QColor c, int w);

protected:
	void paintEvent(QPaintEvent*)override;

private:
	QPixmap Pix;
	int center_x, center_y;
};

