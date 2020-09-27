#pragma once
#include <QObject>
#include <Qpainter>

class Worker:public QObject
{
	Q_OBJECT
public:
	explicit Worker(QObject* parent = 0);
signals:
	void outPix(int const x, int const y, QColor const c, int const w);
public slots:
	void drawImage();
};

