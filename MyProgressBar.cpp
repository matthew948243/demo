#include "MyProgressBar.h"
#include "ui_MyProgressBar.h"
#include <QPushButton>
#include <QPixmap>
MyProgressBar::MyProgressBar(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::MyProgressBar();
	ui->setupUi(this);

	//填充背景色
    setAutoFillBackground(true);

	posx = 0;
	timer = new QTimer;
	this->hide();
	connect(timer, &QTimer::timeout, this, [=]()
		{
			posx += 10;
			step += 50;
			update();
		});
}

MyProgressBar::~MyProgressBar()
{
	delete ui;
}

void MyProgressBar::paintEvent(QPaintEvent* ev)
{

/*
	QPainter pt2(this);//必须要有this 不然画不了
	if (posx > this->width())
	{
		posx = 0;
	}
	QImage img;
	img.load(":/src/qt.jpg");
	img.scaled(10, 10);
	pt2.drawImage(posx, 0, img);*/
	QPainter painter(this);
	QPen pen;
	QBrush bru;
	bru.setColor(Qt::green);
	//设置笔刷样式，是填充还是图片
	bru.setStyle(Qt::SolidPattern); //画刷填充样式
  /*  bru.setStyle(Qt::TexturePattern);*/
	/*pen.setBrush(bru);*/
	painter.setBrush(bru);
	painter.setPen(pen);

	rec.setX(500);
	rec.setY(0);
	rec.setWidth(300);
	rec.setHeight(20);
	
	if (step > this->width())
	{
		step = 0;
	}


	rec.moveTo(0 + step * 1.5, 0);//
	//painter.drawRect(rec);    //draw必须在后面。否则更新不了,或者移动画家？移动画家相当于移动局部坐标系  /*  painter.restore()回退一步; painter.resetTransform();
	
	painter.drawRoundedRect(rec, 5, 5);
/*	painter.drawRoundRect(rec, 5, 5);*/
	painter.resetTransform();
	painter.end();
}
