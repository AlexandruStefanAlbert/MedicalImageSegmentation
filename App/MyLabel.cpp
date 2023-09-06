#include "MyLabel.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QAction>
#include <QFileDialog>
#include <QGroupBox>
#include <iostream>

MyLabel::MyLabel(QWidget* parent): QLabel(parent)
{
    selectionStarted = false;
    newPixmap = this->pixmap();
}

MyLabel::~MyLabel() {}

//setarea diferentelor dintre dimensiunea label-ului si imaginea incarcata
void MyLabel::setDiff(Mat img)
{
    this->_diffX = (this->width() - img.cols) / 2; //this->width() = latimea label-ului
    this->_diffY = (this->height() - img.rows) / 2;//this-> height() = inaltimea label-ului
}
/// <summary>
/// Setarea coordonatelor conturului Snake-ului
/// </summary>
void MyLabel::setContour()
{
    //initializare contour snake cu conturul curent desenat
    newContour = points;

    //aducerea conturului snake la coordonatele conturului desenat
    for (int i = 0; i < points.size(); i++) 
    {
        newContour[i].setX(points[i].x() - _diffX);
        newContour[i].setY(points[i].y() - _diffY);
    }
}

/// <summary>
/// Desenarea conturului de start, de unde incepe Snake-ul sa se restranga pe tumora.
/// </summary>
/// <param name="img"></param>
/// <param name="contour"></param>
void MyLabel::drawStartContour(Mat img, QVector<QPoint>& contour)
{
    int size = contour.size();
    std::vector<cv::Point> points;
   
    setDiff(img);
    setContour();

    for (int i = 0; i < contour.size(); i++)
    {        
        points.push_back(cv::Point(contour[i].x()-_diffX, contour[i].y()-_diffY));
    }
    cv::polylines(img, points, true, cv::Scalar(255, 255, 255), 2.5, Qt::SolidLine);
}

//Internal energy

/// <summary>
/// Calcularea Energiei INTERNE din Algoritmul Snakes Active Contour Model.
/// </summary>
/// <param name="contour"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns>Un vector de puncte ce contine coordonatele noii curbe</returns>
QVector<QPoint> MyLabel::computeInternalEnergy(const QVector<QPoint>& contour, double alpha, double beta)
{    
    QVector<QPoint> internalEnergy(contour.size());
    
    
    for (int i = 0; i < contour.size(); i++) {

        //prev point:        
        QPoint prev = contour[(i - 1 + contour.size()) % contour.size()];
        //next point:
        QPoint next = contour[((i + 1) % contour.size())];
        //current point = contour[i]
        QPoint current = contour[i % contour.size()];
        double dx = current.x() - prev.x();
        double dy = current.y() - prev.y();
        double dist = sqrt(dx*dx + dy*dy);     
        
        internalEnergy[i] = alpha * (next - current)/(dist) + beta * (next - 2 * current + prev)/(dist*dist);
       }
    return internalEnergy;
   
    
}
/// <summary>
/// Calculare Energiei EXTERNE din cadrul Algortimului Snakes Contour Active Model, prin calcularea gradientului imaginii.
/// </summary>
/// <param name="image"></param>
/// <param name="contour"></param>
/// <param name="gamma"></param>
/// <returns>Un vector de puncte ce contine coordonatele gradientului imaginii. (-G(x,y)) </returns>
QVector<QPoint> MyLabel::computeExternalEnergy(const Mat& image, const QVector<QPoint>& contour)
{
    QVector<QPoint> externalEnergy(contour.size());
    
    //Calculate the external energy
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 0);
    cv::Mat gradientX, gradientY;
    
    //gradientul pe X
    cv::Sobel(grayImage, gradientX, CV_32F, 1, 0);

    //gradientul pe Y
    cv::Sobel(grayImage, gradientY, CV_32F, 0, 1);
  
    for (int i = 0; i < contour.size(); i++) {
        QPoint point = contour[i];
        double gx = gradientX.at<float>(point.y(), point.x());
        double gy = gradientY.at<float>(point.y(), point.x());
        //  -gradient(f(x,y))  
        externalEnergy[i] =  QPoint(-(gx), -(gy));
     
    }
    return  externalEnergy;
}
/// <summary>
/// Calcularea energiei totale, ce reprezinta suma dintre Energia Interga si Energia Externa
/// </summary>
/// <param name="image"></param>
/// <param name="contour"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="gamma"></param>
/// <returns>Un vector de puncte ce reprezinta coordonatele Snake-ului</returns>
QVector<QPoint> MyLabel::computeEnergy(const cv::Mat& image, const QVector<QPoint>& contour,  double alpha, double beta, double gamma)
{
    QVector<QPoint> internalEnergy = computeInternalEnergy(contour, alpha, beta);
    QVector<QPoint> externalEnergy = computeExternalEnergy(image, contour);
    QVector<QPoint> totalEnergy(contour.size());

    //energia totala  : internalEnergy + externalEnergy
    for (int i = 0; i < contour.size(); i++) 
    {
        totalEnergy[i] = internalEnergy[i]  + gamma * externalEnergy[i];
    }

    return totalEnergy;
}
/// <summary>
/// Functia de minimizare a energiei totale. La fiecare pas/iteratie se actualizeaza coordonatele curbei initiale 
/// </summary>
/// <param name="contour"></param>
/// <param name="image"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="gamma"></param>
/// <returns>Un vector de puncte ce reprezinta pozitia Snake-ului la fiecare iterate </returns>
QVector<QPoint> MyLabel::minimzeEnergy(QVector<QPoint> contour, const cv::Mat& image, double alpha, double beta, double gamma)

{
    //setDiff(image);
    QVector<QPoint> totalEnergy = computeEnergy(image, contour, alpha, beta, gamma);
        
    //actualizarea conturului 'snake' (newContour)
    for (int i = 0; i < newContour.size(); i++)
    {       
       QPoint pt = newContour[i];
       QPoint _total = totalEnergy[i];
       int newX = pt.x() + (_total.x());
       int newY = pt.y() + (_total.y());
      
        newContour[i] = QPoint(newX, newY); //   totalEnergy[i];          
    }
    return newContour;
}

/// <summary>
/// Un eveniment ce deseneaza pe label-ul imaginii conturul trasat cu mouse-ul
/// </summary>
/// <param name="e"></param>
void MyLabel::paintEvent(QPaintEvent* e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
    
    painter.setPen(QPen(QColor(255, 0, 0), 1.5, Qt::SolidLine));
  
        
    painter.drawPolyline(points);

    emit paint();
}
/// <summary>
/// Eveniment ce se declanseaza la apsararea click-urilor mouse-ului.
/// Pentru click stanga reprezinta inceperea desenarii peste imagine a conturului de start.
/// Pentru click dreapta se sterge conturul din label-ul ce contine imaginea
/// </summary>
/// <param name="e"></param>
void MyLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        
        selectionStarted = true;
        points.push_back(e->pos());
    }
    else
    {
        points.clear();
        this->update();
    }
    
   
}
/// <summary>
/// Miscarea mouselui
/// </summary>
/// <param name="e"></param>
void MyLabel::mouseMoveEvent(QMouseEvent* e)
{
    if (selectionStarted)
    {
        repaint();
    }
 
}
/// <summary>
/// Cand se elibereaza mouse-ului se incheie evenimentul de desenare a punctului din contur.
/// </summary>
/// <param name="e"></param>
void MyLabel::mouseReleaseEvent(QMouseEvent* e)
{
    selectionStarted = false;
   
}