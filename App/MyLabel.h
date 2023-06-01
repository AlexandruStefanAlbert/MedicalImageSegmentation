#include <QLabel>
#include <QMenu>
#include <qgroupbox.h>
#include <QWidget>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;




#pragma once
#ifndef MYLABEL_H
#define MYLABEL_H

class myLabel : public QLabel
{
	

	Q_OBJECT
public:
	bool selectionStarted;
	QMenu contextMenu;
	QVector<QPoint> points; //startContour
	QVector<QPoint> newContour;
	QPixmap newPixmap;
	int diffX, diffY;
	
public:
	
	myLabel(QWidget* parent = 0);
	~myLabel();

	void drawStartContour(Mat img, QVector<QPoint>& contour);
	QVector<QPoint> computeInternalEnergy(const QVector<QPoint>& contour, double alpha, double beta);
	QVector<QPoint> computeExternalEnergy(const Mat& image,  const QVector<QPoint>& contour, double gamma);
	QVector<QPoint> computeEnergy(const cv::Mat& image, const QVector<QPoint>& contour,  double alpha, double beta, double gamma);
	QVector<QPoint> minimzeEnergy(QVector<QPoint> contour,  const cv::Mat& image, double alpha, double beta, double gamma);
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
