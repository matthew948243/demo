#include "MyProgressBar.h"
#include "ui_MyProgressBar.h"
#include <QPushButton>
#include <QPixmap>
MyProgressBar::MyProgressBar(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::MyProgressBar();
	ui->setupUi(this);

	//��䱳��ɫ
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
	QPainter pt2(this);//����Ҫ��this ��Ȼ������
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
	//���ñ�ˢ��ʽ������仹��ͼƬ
	bru.setStyle(Qt::SolidPattern); //��ˢ�����ʽ
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
	//painter.drawRect(rec);    //draw�����ں��档������²���,�����ƶ����ң��ƶ������൱���ƶ��ֲ�����ϵ  /*  painter.restore()����һ��; painter.resetTransform();
	
	painter.drawRoundedRect(rec, 5, 5);
/*	painter.drawRoundRect(rec, 5, 5);*/
	painter.resetTransform();
	painter.end();
}
