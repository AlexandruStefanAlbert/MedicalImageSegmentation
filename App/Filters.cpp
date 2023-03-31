#include "Filters.h"
#include "MyLabel.h"

FiltersClass::FiltersClass()
{
	this->originalImage = 0;
	this->processedImage = 0;
	
}
FiltersClass::~FiltersClass()
{
	this->originalImage.deallocate();
	this->processedImage.deallocate();
}

Mat FiltersClass::convertQImageToMat(QImage &img)
{
	img = img.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
	return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}
QImage  FiltersClass::convertMapToQImage(const cv::Mat& inMat)
{
    switch (inMat.type())
    {
        // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(inMat.data,
            inMat.cols, inMat.rows,
            static_cast<int>(inMat.step),
            QImage::Format_ARGB32);

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(inMat.data,
            inMat.cols, inMat.rows,
            static_cast<int>(inMat.step),
            QImage::Format_RGB888);

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(inMat.data,
            inMat.cols, inMat.rows,
            static_cast<int>(inMat.step),
            QImage::Format_Grayscale8);
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if (sColorTable.isEmpty())
        {
            sColorTable.resize(256);

            for (int i = 0; i < 256; ++i)
            {
                sColorTable[i] = qRgb(i, i, i);
            }
        }

        QImage image(inMat.data,
            inMat.cols, inMat.rows,
            static_cast<int>(inMat.step),
            QImage::Format_Indexed8);

        image.setColorTable(sColorTable);
#endif

        return image;
    }

    default:
        break;
    }

    return QImage();
}

QPixmap FiltersClass::convertMatToQPixmap(Mat &img)
{
	return QPixmap::fromImage(convertMapToQImage(img));
	
}

Mat FiltersClass::adjustContrast(Mat img, double alpha, int beta, double gamma)
{
    
    Mat new_img = Mat::zeros(img.size(), img.type());
    int x1 = select.selectionRect.x(), y1= select.selectionRect.y(), width= select.selectionRect.width(), height= select.selectionRect.height();
 

    for (int y = 0; y <img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            for (int c = 0; c < img.channels(); c++)
            {
                new_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(pow((alpha * img.at<Vec3b>(y, x)[c] + beta)/255,gamma)*255);
            }
        }
    }
    return new_img;
}
Mat FiltersClass::noiseReduceMedian(Mat img)
{
    Mat new_img = Mat::zeros(img.size(), img.type());

    medianBlur(img, new_img, 7);

    return new_img;


}
Mat FiltersClass::noiseReduceGaussian(Mat img)
{
    Mat new_img = Mat::zeros(img.size(), img.type());

    GaussianBlur(img, new_img, Size(5, 5),1,1, 4);

    return new_img;
}

Mat FiltersClass::thresholdButton(Mat img)
{
    Mat new_img;
    
    
    threshold(img, new_img, 200, 255, THRESH_BINARY);
    

    return new_img;
}


Mat FiltersClass::drawContour(Mat img)
{

    std::vector<std::vector<cv::Point>> contours;

    findContours(img, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    Mat contouredImage = img.clone();

    drawContours(contouredImage, contours, -1, Scalar(0, 255, 0), 2);

    return contouredImage;
}
/*Mat FiltersClass::gammaCorrection(Mat img, double gamma)
{
    Mat new_img = Mat::zeros(img.size(), img.type());
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            for (int c = 0; c < img.channels(); c++)
            {
                new_img.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(pow(img.at<Vec3b>(y, x)[c] / 255.0, gamma) * 255.0);
            }
        }
    }
    return new_img;

    
}*/