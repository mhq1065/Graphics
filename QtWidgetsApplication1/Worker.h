#pragma once
#include <QObject>
#include <Qpainter>

class Worker :public QObject
{
	Q_OBJECT
public:
	explicit Worker(QObject* parent = 0);
signals:
	void outPix(int, int, QColor, int);
public slots:
	void dda(int,int,int,int);
	void bresenham(int,int,int,int);
	void oval(int x, int y, int rx, int ry);
	void circle(int x,int y,int r);

private:
	unsigned int t;
};

