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
    QGroupBox* LeftBox;
    QSlider* Contrast;
    QSlider* Brightness;
    QSlider* Gamma;
    QCheckBox* adjustContrast;
    QCheckBox* AdjustBrightness;
    QCheckBox* AdjustGamma;
    QCheckBox* changeColorCheck;
    QSlider* Zoom;
    QToolButton* Toolbox;
    QPushButton* noiseButton;
    QPushButton* thresholdButton;
    QPushButton* detectContourButton;
    QPushButton* drawContourButton;
    QPushButton* playSnakeButton;
    QPushButton* pushButton_6;
    QLabel* label;
    QComboBox* Filters;
    QGroupBox* RightBox;
    QPushButton* LoadNewImage;
    QPushButton* saveAs;
    myLabel* imageLabel;
    QWidget widget;
    QImage image, newImg, processedImg, originalImage, thresholdedImg;
    QString style, boxStyle;
    QRect selectionRect;      
    vector<vector<Point>> contour;
    QMessageBox msg;
    QString styleMainWindow;
    double _alpha, _beta, _gamma;
  

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
    void threshold();
    void detectContour();
    void drawContour();
    void playSnake();
    void changeColor();
};
namespace Ui {
    class MainWindow : public Ui_MainWindow {};    
    
} // namespace Ui

QT_END_NAMESPACE

#endif // MEDICALSEGMENTATIONDKAVCK_H