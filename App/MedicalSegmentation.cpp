#include "MedicalSegmentation.h"
#include "Filters.h"


void Ui_MainWindow::setupUi(QDialog* MainWindow)
{
    buttonsStyle = "QPushButton {background-color : black; color: white; border-style: outset; border-width: 2px; border-radius: 10px;  font: bold 12px;} QPushButton:hover{background-color : rgb(128,128,128); border: 2px solid} QPushButton:focus:pressed{ background-color: rgb(64,64,64) ; } ";
    boxStyle = "background-color: rgb(194, 228, 252); border-style: outset; border-width: 0.5px; border-radius: 10px; ";
    
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");
    MainWindow->resize(931, 672);
    
    QFont font;
    font.setBold(false);
    font.setItalic(false);
    font.setStrikeOut(false);
    MainWindow->setFont(font);
    MainWindow->setCursor(QCursor(Qt::ArrowCursor));

    MainWindow->setStyleSheet("background-color: rgb(230, 244, 254)");

    leftBox = new QGroupBox(MainWindow);
    leftBox->setObjectName("leftBox");
    leftBox->setGeometry(QRect(40, 60, 331, 551));
    leftBox->setAutoFillBackground(true);
    leftBox->setStyleSheet(boxStyle);
    leftBox->setVisible(false);

    contrast = new QSlider(leftBox);
    contrast->setObjectName("contrast");
    contrast->setGeometry(QRect(20, 360, 160, 22));
    contrast->setAutoFillBackground(false);
    contrast->setOrientation(Qt::Horizontal);
    contrast->setRange(10, 300);
    contrast->setPageStep(10);
    contrast->setDisabled(true);

    brightness = new QSlider(leftBox);
    brightness->setObjectName("brightness");
    brightness->setGeometry(QRect(20, 400, 160, 22));
    
    brightness->setValue(0);
    brightness->setOrientation(Qt::Horizontal);
    brightness->setDisabled(true);

    gamma = new QSlider(leftBox);
    gamma->setObjectName("Change_Value");
    gamma->setGeometry(QRect(20, 440, 160, 22));
    gamma->setRange(10, 400);
    gamma->setValue(100);
    gamma->setPageStep(1);
    gamma->setOrientation(Qt::Horizontal);

    adjustContrast = new QCheckBox(leftBox);
    adjustContrast->setObjectName("adjustContrast");
    adjustContrast->setGeometry(QRect(210, 360, 111, 17));
    adjustContrast->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");

    adjustBrightness = new QCheckBox(leftBox);
    adjustBrightness->setObjectName("adjustBrightness");
    adjustBrightness->setGeometry(QRect(210, 400, 111, 20));
    adjustBrightness->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");
    adjustGamma = new QCheckBox(leftBox);
    adjustGamma->setObjectName("adjustGamma");
    adjustGamma->setGeometry(QRect(210, 440, 110, 17));
    adjustGamma->setStyleSheet("border-width: 0px; border-radius: 0px;  font: bold 12px;");
    Zoom = new QSlider(leftBox);
    Zoom->setObjectName("Zoom");
    Zoom->setGeometry(QRect(80, 510, 160, 22));
    Zoom->setValue(50);
    Zoom->setOrientation(Qt::Horizontal);

    Zoom->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");

    noiseButton = new QPushButton(leftBox);
    noiseButton->setObjectName("noiseButton");
    noiseButton->setGeometry(QRect(30, 90, 115, 37));
    noiseButton->setStyleSheet(buttonsStyle);

    thresholdButton = new QPushButton(leftBox);
    thresholdButton->setObjectName("pushButton_2");
    thresholdButton->setGeometry(QRect(170, 90, 115, 37));
    thresholdButton->setStyleSheet(buttonsStyle);

    detectContourButton = new QPushButton(leftBox);
    detectContourButton->setObjectName("pushButton_3");
    detectContourButton->setGeometry(QRect(30, 150, 115, 37));
    detectContourButton->setStyleSheet(buttonsStyle);
   
    drawContourButton = new QPushButton(leftBox);
    drawContourButton->setObjectName("pushButton_4");
    drawContourButton->setGeometry(QRect(170, 150, 115, 37));
    drawContourButton->setStyleSheet(buttonsStyle);
   
    playSnakeButton = new QPushButton(leftBox);
    playSnakeButton->setObjectName("pushButton_5");
    playSnakeButton->setGeometry(QRect(30, 210, 115, 37));
    playSnakeButton->setStyleSheet(buttonsStyle);
   
    watershedButton = new QPushButton(leftBox);
    watershedButton->setObjectName("pushButton_6");
    watershedButton->setGeometry(QRect(170, 210, 115, 37));
    watershedButton->setStyleSheet(buttonsStyle);
   
    label = new QLabel(leftBox);
    label->setObjectName("label");
    label->setGeometry(QRect(140, 480, 41, 21));
    label->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");

    alphaValue = new QLabel(leftBox);
    alphaValue->setObjectName("alpha");
    alphaValue->setGeometry(QRect(80, 340, 80, 15));
    alphaValue->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    alphaValue->setText(QString("Alpha = ") + QString::number(contrast->value()/100, 'f', 2));
    

    betaValue = new QLabel(leftBox);
    betaValue->setObjectName("beta");
    betaValue->setGeometry(QRect(80, 380, 70, 15));
    betaValue->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    betaValue->setText(QString("Beta = ") + QString::number(brightness->value(), 'f', 2));

    gammaValue = new QLabel(leftBox);
    gammaValue->setObjectName("gamma");
    gammaValue->setGeometry(QRect(80, 420, 80, 15));
    gammaValue->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    gammaValue->setText(QString("Gamma = ") + QString::number(gamma->value()/100, 'f', 2));

    QFont font1;
    font1.setFamilies({ QString::fromUtf8("Mongolian Baiti") });
    font1.setPointSize(10);
    font1.setBold(false);
    font1.setItalic(false);
    font1.setStrikeOut(false);
    label->setFont(font1);
    alphaValue->setFont(font1);
    betaValue->setFont(font1);
    filters = new QComboBox(leftBox);
    filters->addItem(QString());
    filters->addItem(QString());
    filters->setObjectName("filters");
    filters->setGeometry(QRect(85, 295, 151, 21));
    rightBox = new QGroupBox(MainWindow);
    rightBox->setObjectName("rightBox");
    rightBox->setGeometry(QRect(410, 60, 491, 551));
    rightBox->setAutoFillBackground(true);
    rightBox->setStyleSheet(boxStyle);

    loadNewImage = new QPushButton(rightBox);
    loadNewImage->setObjectName("loadNewImage");
    loadNewImage->setGeometry(QRect(150, 492, 191, 31));
    loadNewImage->setStyleSheet(buttonsStyle);
    loadNewImage->setFocusPolicy(Qt::TabFocus);
    saveAs = new QPushButton(rightBox);
    saveAs->setObjectName("SaveAs");
    saveAs->setGeometry(QRect(270, 492, 191, 31));
    saveAs->setStyleSheet(buttonsStyle);
    saveAs->setVisible(false);
    imageLabel = new MyLabel(rightBox);
    imageLabel->setObjectName("imageLabel");
    imageLabel->setGeometry(QRect(20, 20, 451, 400));   
    imageLabel->setEnabled(false);

    alphaSnake = new QSlider(rightBox);
    alphaSnake->setObjectName("alpha_Value");
    alphaSnake->setRange(10, 200);
    alphaSnake->setGeometry(QRect(50, 470, 160, 22));
    alphaSnake->setPageStep(10);
    alphaSnake->setVisible(false);
    alphaSnake->setOrientation(Qt::Horizontal);

    betaSnake = new QSlider(rightBox);
    betaSnake->setObjectName("beta_value");
    betaSnake->setGeometry(QRect(270, 470, 160, 22));
    betaSnake->setRange(1, 20);
    betaSnake->setVisible(false);
    betaSnake->setOrientation(Qt::Horizontal);

    alphaSnakeValue = new QLabel(rightBox);
    alphaSnakeValue->setObjectName("alphaSnake");
    alphaSnakeValue->setGeometry(QRect(50, 450, 120, 15));
    alphaSnakeValue->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    alphaSnakeValue->setText(QString("Alpha Snake = ") + QString::number(alphaSnake->value() / static_cast<double>(100), 'f', 2));
    alphaSnakeValue->setVisible(false);
    alphaSnakeValue->setFont(font1);

    betaSnakeValue = new QLabel(rightBox);
    betaSnakeValue->setObjectName("betaSnake");
    betaSnakeValue->setGeometry(QRect(270, 450, 120, 15));
    betaSnakeValue->setStyleSheet("background-color: none; border-width: 0px; border-radius: 0px;");
    betaSnakeValue->setText(QString("Beta Snake = ") + QString::number(betaSnake->value() / static_cast<double>(100), 'f', 2));
    betaSnakeValue->setVisible(false);
    betaSnakeValue->setFont(font1);

    connect(loadNewImage, &QPushButton::released, this, &Ui_MainWindow::loadImage);
    connect(saveAs, &QPushButton::released, this, &Ui_MainWindow::saveImage);
    connect(Zoom, &QSlider::valueChanged, this, &Ui_MainWindow::zoomButton);
    connect(contrast, &QSlider::valueChanged, this, &Ui_MainWindow::contrastButton);
    connect(adjustContrast, &QCheckBox::pressed, this, &Ui_MainWindow::isContrast);
    connect(brightness, &QSlider::valueChanged, this, &Ui_MainWindow::brightnessButton);
    connect(adjustBrightness, &QCheckBox::pressed, this, &Ui_MainWindow::isBrightness);
    connect(gamma, &QSlider::valueChanged, this, &Ui_MainWindow::gammaButton);
    connect(adjustGamma, &QCheckBox::pressed, this, &Ui_MainWindow::isGamma);
    connect(imageLabel, SIGNAL(paint), this, SLOT(paintEvent));
    
    connect(noiseButton, &QPushButton::released, this, &Ui_MainWindow::noise);
    connect(thresholdButton, &QPushButton::released, this, &Ui_MainWindow::thresholded);
    connect(detectContourButton, &QPushButton::released, this, &Ui_MainWindow::detectContour);
    connect(drawContourButton, &QPushButton::released, this, &Ui_MainWindow::drawContour);
    connect(playSnakeButton, &QPushButton::released, this, &Ui_MainWindow::playSnake);
    connect(watershedButton, &QPushButton::released, this, &Ui_MainWindow::applyWatershed);
    connect(alphaSnake, &QSlider::valueChanged, this, &Ui_MainWindow::alphaSnakeSlider);
    connect(betaSnake, &QSlider::valueChanged, this, &Ui_MainWindow::betaSnakeSlider);
    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void Ui_MainWindow::retranslateUi(QDialog* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MedicalSegmentation", nullptr));
    leftBox->setTitle(QString());
    adjustContrast->setText(QCoreApplication::translate("MainWindow", "Adjust contrast", nullptr));
    adjustBrightness->setText(QCoreApplication::translate("MainWindow", "Adjust brightness", nullptr));
    adjustGamma->setText(QCoreApplication::translate("MainWindow", "Adjust gamma", nullptr));
    noiseButton->setText(QCoreApplication::translate("MainWindow", "1. Noise reduce", nullptr));
    thresholdButton->setText(QCoreApplication::translate("MainWindow", "2. Thresholding", nullptr));
    detectContourButton->setText(QCoreApplication::translate("MainWindow", "3. Detect Contour", nullptr));
    drawContourButton->setText(QCoreApplication::translate("MainWindow", "4. Draw Contour", nullptr));
    playSnakeButton->setText(QCoreApplication::translate("MainWindow", "PLAY SNAKE", nullptr));
    watershedButton->setText(QCoreApplication::translate("MainWindow", "WATERSHED", nullptr));

    label->setText(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
    
    filters->setItemText(0, QCoreApplication::translate("MainWindow", "Median Blur", nullptr));
    filters->setItemText(1, QCoreApplication::translate("MainWindow", "Gaussian Blur", nullptr));

    rightBox->setTitle(QString());
    loadNewImage->setText(QCoreApplication::translate("MainWindow", "Load new image", nullptr));
    saveAs->setText(QCoreApplication::translate("MainWindow", "Save as", nullptr));

  

} // retranslateUi
/// <summary>
/// Functie ce detecteaza conturul din imagine
/// </summary>
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

        cv::findContours(gray, contour, RETR_LIST, CHAIN_APPROX_SIMPLE);

        PlaySound(TEXT("sounds/succes.wav"), NULL, SND_FILENAME | SND_ASYNC);
        msg.setText("Contour detected!");
        msg.exec();
        
    }

    else {
        PlaySound(TEXT("sounds/error.wav"), NULL, SND_FILENAME | SND_ASYNC);
        msg.setText("Thresholding image first!");
        msg.exec();
    }

}
/// <summary>
/// Setează valoarea pentru parametrul alpha din ecuatia Snake-ului
/// </summary>
void Ui_MainWindow::alphaSnakeSlider()
{
    this->_alphaSnake = alphaSnake->value() / 100.0;
    alphaSnakeValue->setText(QString("Alpha Snake = ") + QString::number(this->_alphaSnake, 'f', 2));

}
/// <summary>
/// Setează valoarea pentru parametrul beta din ecuatia Snake-ului
/// </summary>
void Ui_MainWindow::betaSnakeSlider()
{
    this->_betaSnake = betaSnake->value() / 10.0;
    betaSnakeValue->setText(QString("Beta Snake = ") + QString::number(this->_betaSnake, 'f', 2));

}

/// <summary>
/// Functie ce reprezinta inceperea algoritmului Snakes Active Contour Model. 
/// Se apeleaza functia de minimizare a energeiei la fiecare iteratie(~150).
/// Se deseneaza Snake-ul si se actualizeaza pozitia acestuia la fiecare iteratie.
/// </summary>
void Ui_MainWindow::playSnake()
{
    
    FiltersClass filters;
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Mat original = filters.convertQImageToMat(image);
    
     Mat _contouredImage = original.clone();
    imageLabel->drawStartContour(_contouredImage, imageLabel->points);
  
   //preprocesare imagine
   //threshold
    threshold(original, original, 120, 255, THRESH_BINARY);

   // Aplicarea operatiei morfologice de deschidere pentru a elimina gaurile sau zgomotul din obiectul segmentat
    Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10));
    morphologyEx(original, original, cv::MORPH_OPEN, structuringElement);    


    int beta = this->_betaSnake;
    //Verific daca conturul sarpelui a fost initializat
    if (!imageLabel->newContour.isEmpty())
    {
        //iterari succesive pentru calcularea noului contur snake
        for (int iter = 1; iter < 150; iter++)
        {
            snakeContour = imageLabel->minimzeEnergy(imageLabel->newContour, original, this->_alphaSnake, this->_betaSnake, 0.05);

            Mat contouredImage = _contouredImage.clone();
            //desenarea snakeContour 
            for (int i = 0; i < snakeContour.size() - 1; i++) {
                cv::Point pt1(snakeContour[i].x(), snakeContour[i].y());
                cv::Point pt2(snakeContour[i + 1].x(), snakeContour[i + 1].y());
                cv::line(contouredImage, pt1, pt2, cv::Scalar(0, 255, 0), 2.5);
            }
            //unirea ultimului punct cu primul
            cv::Point pt1(snakeContour[0].x(), snakeContour[0].y());
            cv::Point pt2(snakeContour.back().x(), snakeContour.back().y());
            cv::line(contouredImage, pt1, pt2, cv::Scalar(0, 255, 0), 2.5);

            originalImage = filters.convertMatToQImage(contouredImage);

            imageLabel->clear();
            //afisarea pe Label a imaginii cu noul contur actualizat
            imageLabel->setPixmap(QPixmap::fromImage(originalImage.scaledToHeight(image.height(), Qt::SmoothTransformation)));
            imageLabel->update();
            QCoreApplication::processEvents();
            QThread::msleep(20);
            processedImg = originalImage;

        }
    }
    else
    {
        msg.setText("Initializeaza conturul!");
        msg.exec();
    }
}


/// <summary>
/// Functie ce deseneaza conturul tumorii detectate peste imaginea originala
/// </summary>
void Ui_MainWindow::drawContour()
{
    //QMessageBox msg;
    if (!contour.empty())
    {
        FiltersClass filters;
        PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Mat original = filters.convertQImageToMat(image);       
        Mat contouredImage = original.clone();   
        drawContours(contouredImage, contour, -1, Scalar(0, 255, 0), 2);

        originalImage = filters.convertMatToQImage(contouredImage);
        imageLabel->clear();
        imageLabel->setPixmap(QPixmap::fromImage(originalImage.scaledToHeight(image.height(), Qt::SmoothTransformation)));
        imageLabel->update();    
        processedImg = originalImage;
    }    
    else
    {
        PlaySound(TEXT("sounds/error.wav"), NULL, SND_FILENAME | SND_ASYNC);
        msg.setText("Detect contour first!");
        msg.exec();
    }
    
    
}
/// <summary>
/// Aplicarea metodei de reducere a zgomotului asupra imaginii. Metoda aleasa se face in functie de filtrul ales 
/// din Selection bar-ul din interfata.
/// </summary>
void Ui_MainWindow::noise()
{
    FiltersClass myFilters;
    
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Mat img = myFilters.convertQImageToMat(image);
    Mat new_img;
    if (filters->currentIndex() == 0)
    {
        imageLabel->clear();
        new_img = myFilters.noiseReduceMedian(img);
    }
    if (filters->currentIndex() == 1)
    {
        imageLabel->clear();        
        new_img = myFilters.noiseReduceGaussian(img);
    }
    image = myFilters.convertMatToQImage(new_img);

    imageLabel->clear();

    
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(image.height(), Qt::SmoothTransformation)));
}
/// <summary>
/// Aplicarea metodei de segmentare a imaginii astfel incat sa se extraga tumora din imagine
/// </summary>
void Ui_MainWindow::thresholded()
{
    FiltersClass filters;
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Mat img = filters.convertQImageToMat(processedImg);
    Mat new_img;
    //Aplicarea funcției thresholdFunction asupra imaginii încărcate
    new_img = filters.thresholdFunction(img);   
    //Convertirea imaginii segmentate într-un obiect QImage
    thresholdedImg = filters.convertMatToQImage(new_img);
    imageLabel->clear();
    //Afișarea pe scena grafică a rezultatului în urma segmentării
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(thresholdedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(thresholdedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));
   
}
void Ui_MainWindow::applyWatershed()
{
    FiltersClass filters;
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Mat img = filters.convertQImageToMat(processedImg);
    Mat new_img;

    new_img = filters.watershedFunction(img);
    watershedImg = filters.convertMatToQImage(new_img);
    imageLabel->clear();
    processedImg = watershedImg;
    //Afișarea pe scena grafică a rezultatului în urma segmentării watershed
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(watershedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(watershedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));

}
/// <summary>
/// Zoom In, Zoom out peste imagine. Functia se apeleaza la actionarea Slide bar-ului de Zoom din interfata.
/// </summary>
void Ui_MainWindow::zoomButton()
{
   
    if(!processedImg.isNull())
        newImg= processedImg.scaledToHeight(imageLabel->height() + Zoom->value() * 3, Qt::SmoothTransformation);
    else
        newImg = image.scaledToHeight(imageLabel->height() + Zoom->value() * 3, Qt::SmoothTransformation);

        imageLabel->clear();

        imageLabel->setPixmap(QPixmap::fromImage(newImg));
        imageLabel->setAlignment(Qt::AlignCenter);
   
}

/// <summary>
/// Imbunatatirea contrastului imaginii. Functie ce se apeleaza la actionarea Slide bar-ului contrast din interfata.
/// </summary>
void Ui_MainWindow::contrastButton()
{        
        FiltersClass filters;
        Mat img = filters.convertQImageToMat(image);
        this->_alpha = contrast->value() / 100.0;
        this->_beta = brightness->value();
        this->_gamma = gamma->value() / 70.0;
        Mat new_img = filters.adjustImage(img,_alpha, _beta, _gamma);

        alphaValue->setText(QString("Alpha = ") + QString::number(this->_alpha, 'f', 2));
        processedImg = filters.convertMatToQImage(new_img);
        imageLabel->clear();
        if (newImg.height())
        {
            imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
        }
        else
            imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));
        
    
   
}
/// <summary>
/// Imbunatatirea luminozitatii imaginii. Functie ce se apeleaza la actionarea Slide bar-ului brightness din interfata.
/// </summary>
void Ui_MainWindow::brightnessButton()
{
    FiltersClass filters;

    Mat img = filters.convertQImageToMat(image);
    this->_alpha = contrast->value() / 100.0;
    this->_beta = brightness->value();
    this->_gamma = gamma->value() / 100.0;
    Mat new_img = filters.adjustImage(img, _alpha, _beta, _gamma);

    betaValue->setText(QString("Beta = ") + QString::number(this->_beta, 'f', 2));

    processedImg = filters.convertMatToQImage(new_img);
    imageLabel->clear();
    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));

}
/// <summary>
/// Imbunatatirea factorului gama a imaginii. Functie ce se apeleaza la actionarea Slide bar-ului contrast din interfata.
/// </summary>
void Ui_MainWindow::gammaButton()
{
    FiltersClass filters;
    Mat img = filters.convertQImageToMat(image);
    this->_alpha = contrast->value() / 100.0;
    this->_beta = brightness->value();
    this->_gamma = gamma->value() / 70.0;
    Mat new_img = filters.adjustImage(img, _alpha, _beta,_gamma);

    gammaValue->setText(QString("Gamma = ") + QString::number(this->_gamma, 'f', 2));

    processedImg = filters.convertMatToQImage(new_img);
    imageLabel->clear();

    if (newImg.height())
    {
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(newImg.height(), Qt::SmoothTransformation)));
    }
    else
        imageLabel->setPixmap(QPixmap::fromImage(processedImg.scaledToHeight(image.height(), Qt::SmoothTransformation)));


}
/// <summary>
/// Bifarea/Debifarea pentru ajustarea contrastului.
/// </summary>
void Ui_MainWindow::isContrast()
{

    
    if (!adjustContrast->isChecked())
    {
        PlaySound(TEXT("sounds/onClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        contrast->setEnabled(true);             
    }
    else
    {
        PlaySound(TEXT("sounds/offClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        contrast->setDisabled(true);
    }
}
/// <summary>
/// Bifarea/Debifarea pentru ajustarea luminozitatii.
/// </summary>
void Ui_MainWindow::isBrightness()
{
    if (!adjustBrightness->isChecked())
    {
        PlaySound(TEXT("sounds/onClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        brightness->setEnabled(true);
    }
    else
    {
        PlaySound(TEXT("sounds/offClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        brightness->setDisabled(true);
    }
}
/// <summary>
/// Bifarea/Debifarea pentru ajustarea factorului gamma.
/// </summary>
void Ui_MainWindow::isGamma()
{
    if (!adjustGamma->isChecked())
    {
        PlaySound(TEXT("sounds/onClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gamma->setEnabled(true);
    }
    else
    {
        PlaySound(TEXT("sounds/offClick.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gamma->setDisabled(true);
    }

}


/// <summary>
/// Incarcarea imaginii in interfata
/// </summary>
void Ui_MainWindow::loadImage()
{
    FiltersClass filters;
    imageLabel->clear();
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
    QString path = QFileDialog::getOpenFileName(&widget, tr("Choose"), "", tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    if (QString::compare(path, QString()) != 0)
    {

        bool valid = image.load(path);
        if (valid)
        {
            imageLabel->setEnabled(true);
            image = image.scaledToWidth(imageLabel->height() //+ Zoom->value()
                , Qt::SmoothTransformation);
            originalImage = image;
           
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->setAlignment(Qt::AlignCenter);
            saveAs->setVisible(true);
            loadNewImage->setGeometry(QRect(30, 492, 191, 31));
            leftBox->setVisible(true);
            Zoom->setValue(50);
            contrast->setValue(100);
            contrast->setEnabled(true);
            adjustContrast->setChecked(true);
            brightness->setEnabled(true);
            adjustBrightness->setChecked(true);
            alphaSnake->setVisible(true);
            betaSnake->setVisible(true);
            adjustGamma->setChecked(true);
            gamma->setEnabled(true);
            gamma->setValue(100);
            alphaSnakeValue->setVisible(true);
            betaSnakeValue->setVisible(true);
            this->_alpha = contrast->value() / 100.0;
            this->_beta = brightness->value();
            this->_gamma = gamma->value() / 70.0;
            alphaSnake->setValue(100);
            betaSnake->setValue(2);
            betaSnake->setPageStep(5);
            this->_alphaSnake = alphaSnake->value() / 100.0;
            this->_betaSnake = betaSnake->value() / 10.0;
        }
        else
        {

        }
    }
}
/// <summary>
/// Salvarea imaginii
/// </summary>
void Ui_MainWindow::saveImage()
{
    PlaySound(TEXT("sounds/click2.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
        PlaySound(TEXT("sounds/succes.wav"), NULL, SND_FILENAME | SND_ASYNC);
        msg.setText("Successfully saved!");
        msg.exec();
        
    }
}
