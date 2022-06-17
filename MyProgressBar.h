#pragma once

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>//声明画家类型
#include<QPixmap>
#include<QTimer>
namespace Ui { class MyProgressBar; };

class MyProgressBar : public QWidget
{
	Q_OBJECT

public:
	MyProgressBar(QWidget *parent = Q_NULLPTR);
	~MyProgressBar();
	void paintEvent(QPaintEvent* ev);
	int posx{};
	QRect rec;
	int step = 0;
	QTimer* timer;
private:
	Ui::MyProgressBar *ui;
};
