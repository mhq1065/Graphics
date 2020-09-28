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
	void dda();
	void bresenham();
	void oval();
};

