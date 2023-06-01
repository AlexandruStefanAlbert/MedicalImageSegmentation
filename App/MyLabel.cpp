#include "MyLabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QAction>
#include <QFileDialog>
#include <QGroupBox>
#include <iostream>

myLabel::myLabel(QWidget* parent): QLabel(parent)
{
    selectionStarted = false;
    newPixmap = this->pixmap();
}

myLabel::~myLabel() {}


void myLabel::drawStartContour(Mat img, QVector<QPoint>& contour)
{
    int size = contour.size();
    std::vector<cv::Point> points;
    int x = this->width();
    int y = this->height();

    diffX = (x - img.cols)/2;
    diffY = (y - img.rows)/2;
    for (int i = 0; i < contour.size(); i++)
    {
        points.push_back(cv::Point(contour[i].x()-diffX, contour[i].y()-diffY));
    }
   // cv::polylines(img, points, true, cv::Scalar(255, 0, 0), 1.5, Qt::SolidLine);
}

//Internal energy

QVector<QPoint> myLabel::computeInternalEnergy(const QVector<QPoint>& contour, double alpha, double beta)
{    
    QVector<QPoint> internalEnergy(contour.size());
    for (int i = 0; i < contour.size(); i++) {
        //prev point:
        QPoint prev = contour[(i - 1 + contour.size()) % contour.size()];
        //next point:
        QPoint next = contour[(i + 1) % contour.size()]; 
        //current point = contour[i]
        double dx = contour[i].x() - prev.x();
        double dy =  contour[i].y() - prev.y();
        double dist = sqrt(dx*dx + dy*dy);
        internalEnergy[i] = alpha * (contour[i] - prev) / dist + 
            (beta* (prev + next - 2 * contour[i]) / (dist * dist));       
    }
    return internalEnergy;
}

QVector<QPoint> myLabel::computeExternalEnergy(const Mat& image, const QVector<QPoint>& contour, double gamma)
{
    QVector<QPoint> externalEnergy(contour.size());
    //Calculate the external energy
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::Mat gradientX, gradientY;
    Mat magnitude, angle;
    //gradientul pe X
    cv::Sobel(grayImage, gradientX, CV_32F, 1, 0);
    
    //gradientul pe Y
    cv::Sobel(grayImage, gradientY, CV_32F, 0, 1);
  
    for (int i = 0; i < contour.size(); i++) {
        QPoint pt = contour[i];
        double gx = gradientX.at<float>(pt.y(), pt.x());
        double gy = gradientY.at<float>(pt.y(), pt.x());
        //  -gradient(f(x,y))
        externalEnergy[i] = QPoint((gx), (gy));
    }
    return externalEnergy;
}

QVector<QPoint> myLabel::computeEnergy(const cv::Mat& image, const QVector<QPoint>& contour,  double alpha, double beta, double gamma)
{
    QVector<QPoint> internalEnergy = computeInternalEnergy(contour, alpha, beta);
    QVector<QPoint> externalEnergy = computeExternalEnergy(image, contour, gamma);
    QVector<QPoint> totalGradient(contour.size());

    //energia totala  : internalEnergy + externalEnergy
    for (int i = 0; i < contour.size(); i++) 
    {
        totalGradient[i] = internalEnergy[i] + externalEnergy[i];        
    }

    return totalGradient;
}

QVector<QPoint> myLabel::minimzeEnergy(QVector<QPoint> contour, const cv::Mat& image, double alpha, double beta, double gamma)

{
   
    QVector<QPoint> totalEnergy = computeEnergy(image, contour, alpha, beta, gamma);
        
    //actualizarea conturului 'snake' (newContour)
    for (int i = 0; i < newContour.size(); i++)
    {    
        QPoint pt = newContour[i];
        QPoint _gradient = totalEnergy[i];
        int newX = pt.x() + (gamma * _gradient.x());
        int newY = pt.y() + (gamma * _gradient.y());
        newContour[i] = QPoint(newX, newY); //   totalEnergy[i];          
    }
    return newContour;
}


void myLabel::paintEvent(QPaintEvent* e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    
    painter.setPen(QPen(QColor(255, 0, 0), 1.5, Qt::SolidLine));
    //painter.setBrush(QBrush(QColor(0, 0, 0)));

    //painter.drawRect(selectionRect);
       
    
    painter.drawPolyline(points);

   
    emit paint();
}

void myLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        //if (selectionRect.contains(e->pos()))
            //contextMenu.exec(this->mapToGlobal(e->pos()));
        selectionStarted = true;
    }
    else
    {
        points.clear();
        this->update();
    }
    
    points.push_back(e->pos());
    emit mousePress();
}

void myLabel::mouseMoveEvent(QMouseEvent* e)
{
    if (selectionStarted)
    {
        repaint();
    }
    emit mouseMove();
}

void myLabel::mouseReleaseEvent(QMouseEvent* e)
{
    selectionStarted = false;
    
    emit mouseRelease();
}