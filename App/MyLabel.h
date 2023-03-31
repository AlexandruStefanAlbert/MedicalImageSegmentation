#include <QLabel>
#include <QMenu>
#include <qgroupbox.h>
#include <QWidget>
#include <opencv2/core/types.hpp>


#pragma once
#ifndef MYLABEL_H
#define MYLABEL_H

class myLabel : public QLabel
{
	

	Q_OBJECT
public:
	bool selectionStarted;
	QRect selectionRect;
	QMenu contextMenu;
	
	
	
public:
	QImage img;
	myLabel(QWidget* parent = 0);
	~myLabel();

public slots:
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

signals:
	void mousePress();
	void paint();
	void mouseMove();
	void mouseRelease();

};


#endif // !MYLABEL_H
