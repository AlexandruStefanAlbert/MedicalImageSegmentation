#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QMenu>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <qfiledialog.h>
#include <qguiapplication.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "MyLabel.h"

#pragma once
#ifndef FILTERS_H
#define FILTERS_H



//#include "MedicalSegmentation.h"


using namespace cv;
using namespace std;


class FiltersClass {

public:
	
	
	FiltersClass();
	~FiltersClass();

	Mat convertQImageToMat(QImage &image);
	QImage convertMapToQImage(const Mat& inMat);
	Mat adjustImage(Mat img, double alpha, int beta, double gamma);
	Mat noiseReduceMedian(Mat img);
	Mat noiseReduceGaussian(Mat img);
	Mat thresholdFunction(Mat img);
	Mat watershedFunction(Mat img);
};


#endif // !FILTERS_H