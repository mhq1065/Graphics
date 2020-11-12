#pragma once
#include <QObject>
#include <Qpainter>

class Worker :public QObject
{
	Q_OBJECT
public:
	explicit Worker(int,int,QObject* parent = 0);
signals:
	void outPix(int, int, QColor, int);
signals:
	void outMsg();
public slots:
	void dda(int,int,int,int);
	void bresenham(int,int,int,int);
	void oval(int x, int y, int rx, int ry);
	void circle(int x,int y,int r);

private:
	unsigned int t;
	int height;
	int width;
	bool isOut(int,int);
};

