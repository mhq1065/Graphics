#include "QtWidgetsApplication1.h"

#include <Qpainter>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include <Qtimer>

// https://blog.csdn.net/sigmarising/article/details/79920380
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// �½��̴߳���ͼ�Լ���ʱ
	worker = new Worker;
	m_thread = new QThread;
	worker->moveToThread(m_thread);
	m_thread->start();
	// ��ʼ��
	Pix = QPixmap(600, 600);
	Pix.fill(Qt::white);
	// ����ͼ
	connect(ui.actionbreshen, SIGNAL(triggered()), worker, SLOT(bresenham()));
	connect(ui.actionDDa, SIGNAL(triggered()), worker, SLOT(dda()));
	connect(ui.actionoval, SIGNAL(triggered()), worker, SLOT(oval())); 
	connect(ui.actioncircle, SIGNAL(triggered()), worker, SLOT(circle()));

	// ���ջ����ź�
	connect(worker, SIGNAL(outPix(int, int, QColor, int)), this, SLOT(draw_point(int, int, QColor, int)), Qt::QueuedConnection);
	// ��ʼ�߳�
	m_thread->start();
}
void QtWidgetsApplication1::paintEvent(QPaintEvent*) {
	QPainter Painter(this);
	Painter.drawPixmap(0, 0, 600, 600, Pix);
}
void QtWidgetsApplication1::draw_point(int  x, int  y, QColor  c, int  w) {
	//qDebug() << x << y << '\n';
	QPainter Painter(&Pix);
	Painter.setPen(QPen(c, w));
	Painter.translate(200, 200);
	Painter.scale(1, -1);
	Painter.drawPoint(x, y);
	this->update();
}