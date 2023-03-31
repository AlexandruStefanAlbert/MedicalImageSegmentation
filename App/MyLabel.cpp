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
    
}

myLabel::~myLabel() {};

void myLabel::paintEvent(QPaintEvent* e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);
  
    painter.setPen(QPen(QColor(255, 0, 0), 1.5, Qt::SolidLine));
    //painter.setBrush(QBrush(QColor(0, 0, 0)));

    painter.drawRect(selectionRect);
    
  
   
    emit paint();
}

void myLabel::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        if (selectionRect.contains(e->pos()))
            contextMenu.exec(this->mapToGlobal(e->pos()));
        
    }
    else
    {
        selectionStarted = true;
        selectionRect.setTopLeft(e->pos());
        selectionRect.setBottomRight(e->pos());
        
    }
    
    emit mousePress();
}

void myLabel::mouseMoveEvent(QMouseEvent* e)
{
    if (selectionStarted)
    {
        selectionRect.setBottomRight(e->pos());
        repaint();
    }
    emit mouseMove();
}

void myLabel::mouseReleaseEvent(QMouseEvent* e)
{
    selectionStarted = false;
    
    emit mouseRelease();
}