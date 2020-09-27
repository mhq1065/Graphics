#include "Worker.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <Qpainter>

Worker::Worker(QObject* parent)
{
}

void Worker::drawImage()
{
	for (int i = 1; i < 10; i++)
	{
		//QThread::sleep(1);
		qDebug() << i << '\n';
		emit outPix(i, i, Qt::red,1);
	}
}
