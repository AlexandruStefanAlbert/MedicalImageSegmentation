#pragma once
#ifndef MEDICALSEGMENTATIONDKAVCK_H
#define MEDICALSEGMENTATIONDKAVCK_H
#include <windows.h>
#include "MyLabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
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
#include <qmenubar.h>
#include <QThread>


using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE



class Ui_MainWindow: public QObject
{
private:
    QGroupBox* leftBox;
    QGroupBox* rightBox;
    QSlider* contrast;
    QSlider* brightness;
    QSlider* gamma;
    QSlider* Zoom;
    QSlider* alphaSnake;
    QSlider* betaSnake;

    QCheckBox* adjustContrast;
    QCheckBox* adjustBrightness;
    QCheckBox* adjustGamma;
       
    QToolButton* toolbox;
    QPushButton* noiseButton;
    QPushButton* thresholdButton;
    QPushButton* detectContourButton;
    QPushButton* drawContourButton;
    QPushButton* playSnakeButton;
    QPushButton* watershedButton;
    QPushButton* loadNewImage;
    QPushButton* saveAs;
    QLabel* label;
    QLabel* alphaValue, *betaValue, *gammaValue, *alphaSnakeValue, *betaSnakeValue;
    QComboBox* filters;
    MyLabel* imageLabel;
    QWidget widget;
    QImage image, newImg, processedImg, originalImage, thresholdedImg, watershedImg;
    QString buttonsStyle, boxStyle;
    QRect selectionRect;      
    vector<vector<Point>> contour;
    QMessageBox msg;
    QString styleMainWindow;
    double _alpha, _beta, _gamma;
    double _alphaSnake, _betaSnake;
    QVector<QPoint> snakeContour;

public:
    
    void setupUi(QDialog* MainWindow);
    void retranslateUi(QDialog* MainWindow);
    void zoomButton();    
    void loadImage();     
    void saveImage();
    void contrastButton();
    void brightnessButton();
    void gammaButton();
    void isContrast();
    void isBrightness();
    void isGamma();
    void noise();
    void thresholded();
    void detectContour();
    void drawContour();
    void playSnake();
    void applyWatershed();
    void alphaSnakeSlider();
    void betaSnakeSlider();
};
namespace Ui {
    class MainWindow : public Ui_MainWindow {};    
    
} // namespace Ui

QT_END_NAMESPACE

#endif // MEDICALSEGMENTATIONDKAVCK_H