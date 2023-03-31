#include "MedicalSegmentation.h"
#include "Filters.h"


void Ui_MainWindow::setupUi(QDialog* MainWindow)
{
    style = "background-color : black; color: white; border-style: outset; border-width: 2px; border-radius: 10px;  font: bold 12px; ";
    boxStyle = "background-color: rgb(194, 228, 252); border-style: outset; border-width: 0.5px; border-radius: 10px; ";
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");
    MainWindow->resize(931, 672);
    menu = new QMenuBar;
    file = new QMenu();
  
    file = menu->addMenu(tr("&File"));

    QFont font;
    font.setBold(false);
    font.setItalic(false);
    font.setStrikeOut(false);
    MainWindow->setFont(font);
    MainWindow->setCursor(QCursor(Qt::ArrowCursor));
    MainWindow->setStyleSheet("background-color: rgb(230, 244, 254)");

    LeftBox = new QGroupBox(MainWindow);
    LeftBox->setObjectName("LeftBox");
    LeftBox->setGeometry(QRect(40, 60, 331, 551));
    LeftBox->setAutoFillBackground(true);
    LeftBox->setStyleSheet(boxStyle);
    LeftBox->setVisible(false);

    Contrast = new QSlider(LeftBox);
    Contrast->setObjectName("Contrast");
    Contrast->setGeometry(QRect(20, 360, 160, 22));
    Contrast->setAutoFillBackground(false);
    Contrast->setOrientation(Qt::Horizontal);
    Contrast->setRange(10, 300);
    Contrast->setPageStep(10);
    Contrast->setDisabled(true);

    Brightness = new QSlider(LeftBox);
    Brightness->setObjectName("Brightness");
    Brightness->setGeometry(QRect(20, 400, 160, 22));
    Brightness->setValue(0);
    Brightness->setOrientation(Qt::Horizontal);
    Brightness->setDisabled(true);

    Gamma = new QSlider(LeftBox);
    Gamma->setObjectName("Change_Value");
    Gamma->setGeometry(QRect(20, 440, 160, 22));
    Gamma->setRange(10, 400);
    Gamma->setValue(100);
    Gamma->setPageStep(1);
    Gamma->setOrientation(Qt::Horizontal);
    AdjustContrast = new QCheckBox(LeftBox);
    AdjustContrast->setObjectName("AdjustContrast");
    AdjustContrast->setGeometry(QRect(210, 360, 111, 17));
    AdjustContrast->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");
    AdjustBrightness = new QCheckBox(LeftBox);
    AdjustBrightness->setObjectName("AdjustBrightness");
    AdjustBrightness->setGeometry(QRect(210, 400, 111, 20));
    AdjustBrightness->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");
    AdjustGamma = new QCheckBox(LeftBox);
    AdjustGamma->setObjectName("AdjustGamma");
    AdjustGamma->setGeometry(QRect(210, 440, 110, 17));
    AdjustGamma->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");
    Zoom = new QSlider(LeftBox);
    Zoom->setObjectName("Zoom");
    Zoom->setGeometry(QRect(80, 510, 160, 22));
    Zoom->setValue(50);
    Zoom->setOrientation(Qt::Horizontal);

    Zoom->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    Toolbox = new QToolButton(LeftBox);
    Toolbox->setObjectName("Toolbox");
    Toolbox->setGeometry(QRect(230, 290, 51, 31));
    noiseButton = new QPushButton(LeftBox);
    noiseButton->setObjectName("noiseButton");
    noiseButton->setGeometry(QRect(30, 40+50, 115, 37));
    noiseButton->setStyleSheet(style);
    thresholdButton = new QPushButton(LeftBox);
    thresholdButton->setObjectName("pushButton_2");
    thresholdButton->setGeometry(QRect(170, 40+50, 115, 37));
    thresholdButton->setStyleSheet(style);
    detectContourButton = new QPushButton(LeftBox);
    detectContourButton->setObjectName("pushButton_3");
    detectContourButton->setGeometry(QRect(30, 100+50, 115, 37));
    detectContourButton->setStyleSheet(style);
    drawContourButton = new QPushButton(LeftBox);
    drawContourButton->setObjectName("pushButton_4");
    drawContourButton->setGeometry(QRect(170, 100+50, 115, 37));
    drawContourButton->setStyleSheet(style);
    /*pushButton_5 = new QPushButton(LeftBox);
    pushButton_5->setObjectName("pushButton_5");
    pushButton_5->setGeometry(QRect(30, 170, 111, 37));
    pushButton_5->setStyleSheet(style);
    pushButton_6 = new QPushButton(LeftBox);
    pushButton_6->setObjectName("pushButton_6");
    pushButton_6->setGeometry(QRect(170, 170, 111, 37));
    pushButton_6->setStyleSheet(style);*/
    label = new QLabel(LeftBox);
    label->setObjectName("label");
    label->setGeometry(QRect(140, 480, 41, 21));
    label->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    QFont font1;
    font1.setFamilies({ QString::fromUtf8("Mongolian Baiti") });
    font1.setPointSize(10);
    font1.setBold(false);
    font1.setItalic(false);
    font1.setStrikeOut(false);
    label->setFont(font1);
    Filters = new QComboBox(LeftBox);
    Filters->addItem(QString());
    Filters->addItem(QString());
    Filters->setObjectName("Filters");
    Filters->setGeometry(QRect(50, 295, 151, 21));
    RightBox = new QGroupBox(MainWindow);
    RightBox->setObjectName("RightBox");
    RightBox->setGeometry(QRect(410, 60, 491, 551));
    RightBox->setAutoFillBackground(true);
    RightBox->setStyleSheet(boxStyle);
    /*graphicsView = new QGraphicsView(RightBox);
    graphicsView->setObjectName("graphicsView");
    graphicsView->setGeometry(QRect(20, 20, 451, 400));
    graphicsView->setAutoFillBackground(true);*/

    LoadNewImage = new QPushButton(RightBox);
    LoadNewImage->setObjectName("LoadNewImage");
    LoadNewImage->setGeometry(QRect(150, 492, 191, 31));
    LoadNewImage->setStyleSheet(style);
    LoadNewImage->setFocusPolicy(Qt::TabFocus);
    saveAs = new QPushButton(RightBox);
    saveAs->setObjectName("SaveAs");
    saveAs->setGeometry(QRect(270, 492, 191, 31));
    saveAs->setStyleSheet(style);
    saveAs->setVisible(false);
    imageLabel = new myLabel(RightBox);
    imageLabel->setObjectName("imageLabel");
    imageLabel->setGeometry(QRect(20, 20, 451, 400));

   
    imageLabel->setEnabled(false);

    connect(LoadNewImage, &QPushButton::released, this, &Ui_MainWindow::loadImage);
    connect(saveAs, &QPushButton::released, this, &Ui_MainWindow::saveImage);
    connect(Zoom, &QSlider::valueChanged, this, &Ui_MainWindow::zoomButton);
    connect(Contrast, &QSlider::valueChanged, this, &Ui_MainWindow::contrastButton);
    connect(AdjustContrast, &QCheckBox::pressed, this, &Ui_MainWindow::isContrast);
    connect(Brightness, &QSlider::valueChanged, this, &Ui_MainWindow::brightnessButton);
    connect(AdjustBrightness, &QCheckBox::pressed, this, &Ui_MainWindow::isBrightness);
    connect(Gamma, &QSlider::valueChanged, this, &Ui_MainWindow::gammaButton);
    connect(AdjustGamma, &QCheckBox::pressed, this, &Ui_MainWindow::isGamma);
    connect(imageLabel, SIGNAL(paint), this, SLOT(paintEvent));
   /* connect(imageLabel, SIGNAL(mouseRelease), this, SLOT(mouseReleaseEvent));
    connect(imageLabel, SIGNAL(mousePress), this, SLOT(mousePressEvent));
    connect(imageLabel, SIGNAL(mouseMove), this, SLOT(mouseMoveEvent));*/
    
    connect(noiseButton, &QPushButton::released, this, &Ui_MainWindow::noise);
    connect(thresholdButton, &QPushButton::released, this, &Ui_MainWindow::threshold);
    connect(detectContourButton, &QPushButton::released, this, &Ui_MainWindow::detectContour);
    connect(drawContourButton, &QPushButton::released, this, &Ui_MainWindow::drawContour);
    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void Ui_MainWindow::retranslateUi(QDialog* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MedicalSegmentation", nullptr));
    MainWindow->setWindowIcon(QIcon("E:/Desktop/PIU/MedicalSegmentation/icon.png"));
    LeftBox->setTitle(QString());
    AdjustContrast->setText(QCoreApplication::translate("MainWindow", "Adjust Contrast", nullptr));
    AdjustBrightness->setText(QCoreApplication::translate("MainWindow", "Adjust Brightness", nullptr));
    AdjustGamma->setText(QCoreApplication::translate("MainWindow", "Adjust Gamma", nullptr));
    Toolbox->setText(QCoreApplication::translate("MainWindow", "Toolbox", nullptr));
    noiseButton->setText(QCoreApplication::translate("MainWindow", "1. Noise reduce", nullptr));
    thresholdButton->setText(QCoreApplication::translate("MainWindow", "2. Thresholding", nullptr));
    detectContourButton->setText(QCoreApplication::translate("MainWindow", "3. Detect Contour", nullptr));
    drawContourButton->setText(QCoreApplication::translate("MainWindow", "4. Draw Contour", nullptr));
    /*pushButton_5->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    pushButton_6->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));*/
    label->setText(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
    
    Filters->setItemText(0, QCoreApplication::translate("MainWindow", "Median Blur", nullptr));
    Filters->setItemText(1, QCoreApplication::translate("MainWindow", "Gaussian Blur", nullptr));

    RightBox->setTitle(QString());
    LoadNewImage->setText(QCoreApplication::translate("MainWindow", "Load new image", nullptr));
    saveAs->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));

  

} // retranslateUi

void Ui_MainWindow::detectContour()
{
    //QMessageBox msg;
    
    if (!thresholdedImg.isNull())
    {
        FiltersClass filters;

        Mat img = filters.convertQImageToMat(thresholdedImg);

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Mat thresholded;
        cv::threshold(gray, thresholded, 1, 255, cv::THRESH_BINARY);

        cv::findContours(thresholded, contour, RETR_LIST, CHAIN_APPROX_SIMPLE);

        msg.setText("Contour detected!");
        msg.exec();
    }

    else {
        msg.setText("Thresholding image first!");
        msg.exec();
    }

}

void Ui_MainWindow::drawContour()
{
    //QMessageBox msg;
    if (!contour.empty())
    {
        FiltersClass filters;

        Mat original = filters.convertQImageToMat(image);

        Mat contouredImage = original.clone();
        drawContours(contouredImage, contour, -1, Scalar(0, 255, 0), 2);


        originalImage = filters.convertMapToQImage(contouredImage);

        imageLabel->clear();

        imageLabel->setPixmap(QPixmap::fromImage(originalImage.scaledToHeight(image.height(), Qt::SmoothTransformation)));

        processedImg = originalImage;
    }
    else
    {
        msg.setText("Detect contour first!");
        msg.exec();
    }
    
    
}

void Ui_MainWindow::noise()
{
    FiltersClass filters;

    Mat img = filters.convertQImageToMat(image);
    Mat new_img;
    if (Filters->currentIndex() == 0)
    {
        imageLabel->clear();
        new_img = filters.noiseReduceMedian(img);
    }
    if (Filters->currentIndex() == 1)
    {
        imageLabel->clear();        
        new_img = filters.noiseReduceGaussian(img);
    }
    image = filters.convertMapToQImage(new_img);

    imageLabel->clear();

    
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
}

void Ui_MainWindow::threshold()
{
    FiltersClass filters;

    Mat img = filters.convertQImageToMat(processedImg);
    Mat new_img;

    new_img = filters.thresholdButton(img);

    thresholdedImg = filters.convertMapToQImage(new_img);
    imageLabel->clear();

    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(thresholdedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(thresholdedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));
   
}
void Ui_MainWindow::zoomButton()
{
   
    //image = image.scaledToWidth(graphicsView->width() + Zoom->value(), Qt::SmoothTransformation);
    if(!processedImg.isNull())
        newImg= processedImg.scaledToHeight(imageLabel->height() + Zoom->value() * 3, Qt::SmoothTransformation);
    else
        newImg = image.scaledToHeight(imageLabel->height() + Zoom->value() * 3, Qt::SmoothTransformation);

        imageLabel->clear();

        imageLabel->setPixmap(QPixmap::fromImage(newImg));
        imageLabel->setAlignment(Qt::AlignCenter);
    
       
       
}
void Ui_MainWindow::brightnessButton()
{
    FiltersClass filters;
    
    Mat img = filters.convertQImageToMat(image);
    Mat new_img = filters.adjustContrast(img, Contrast->value() / 100.0, Brightness->value(), Gamma->value()/100.0);


    processedImg = filters.convertMapToQImage(new_img);
    imageLabel->clear();
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));

}
void Ui_MainWindow::contrastButton()
{        
        FiltersClass filters;
        Mat img = filters.convertQImageToMat(image);
        Mat new_img = filters.adjustContrast(img, Contrast->value()/100.0, Brightness->value(), Gamma->value()/100.0);

    
        processedImg = filters.convertMapToQImage(new_img);
        imageLabel->clear();
        if (newImg.height())
        {
            imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
        }
        else
            imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));
        
    
   
}
void Ui_MainWindow::gammaButton()
{
    FiltersClass filters;
    Mat img = filters.convertQImageToMat(image);

    Mat new_img = filters.adjustContrast(img, Contrast->value() / 100.0, Brightness->value(), Gamma->value()/100.0);

    processedImg = filters.convertMapToQImage(new_img);
    imageLabel->clear();

    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));


    /**/
}
void Ui_MainWindow::isContrast()
{
    QRect selectionZone = imageLabel->selectionRect;
    if (!AdjustContrast->isChecked())
    {
       // imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
        Contrast->setEnabled(true);             
    }
    else
    {
        Contrast->setDisabled(true);
        //imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
    }
}

void Ui_MainWindow::isBrightness()
{
    if (!AdjustBrightness->isChecked())
    {
        Brightness->setEnabled(true);
       // imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
    }
    else
    {
        Brightness->setDisabled(true);
        //imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
    }
}
void Ui_MainWindow::isGamma()
{
    if (!AdjustGamma->isChecked())
    {
        Gamma->setEnabled(true);
    }
    else
    {
        Gamma->setDisabled(true);
    }

}


void Ui_MainWindow::loadImage()
{
    FiltersClass filters;
    imageLabel->clear();
    QString path = QFileDialog::getOpenFileName(&widget, tr("Choose"), "", tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    if (QString::compare(path, QString()) != 0)
    {

        bool valid = image.load(path);
        if (valid)
        {
            imageLabel->setEnabled(true);
            image = image.scaledToWidth(imageLabel->width() + Zoom->value() * 3, Qt::SmoothTransformation);
            originalImage = image;
           
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->setAlignment(Qt::AlignCenter);
            saveAs->setVisible(true);
            LoadNewImage->setGeometry(QRect(30, 492, 191, 31));
            LeftBox->setVisible(true);
            Zoom->setValue(50);
            Contrast->setValue(100);
            Contrast->setEnabled(false);
            AdjustContrast->setChecked(false);
            Brightness->setEnabled(false);
            AdjustBrightness->setChecked(false);

            AdjustGamma->setChecked(false);
            Gamma->setEnabled(false);
            Gamma->setValue(100);
        }
        else
        {

        }
    }
}

void Ui_MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(&widget, tr("Save Image File"), QString(), tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty())
    {
        if (!processedImg.isNull())
        {
            processedImg.save(fileName);
        }
        else
        {
            image.save(fileName);
        }
        msg.setText("Successfully saved!");
        msg.exec();

    }
}
