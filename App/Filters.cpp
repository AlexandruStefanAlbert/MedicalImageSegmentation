#include "Filters.h"
#include "MyLabel.h"

FiltersClass::FiltersClass()
{
		
}
FiltersClass::~FiltersClass()
{
	
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


Mat FiltersClass::adjustImage(Mat img, double alpha, int beta, double gamma)
{
    
    Mat new_img = Mat::zeros(img.size(), img.type()); 

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

    medianBlur(img, new_img, 5);

    return new_img;


}

Mat FiltersClass::noiseReduceGaussian(Mat img)
{
    Mat new_img = Mat::zeros(img.size(), img.type());

    GaussianBlur(img, new_img, Size(5, 5),1.0);

    return new_img;
}

Mat FiltersClass::thresholdFunction(Mat img)
{
    Mat new_img;
   
    //cvtColor(img, img, COLOR_BGR2GRAY);
    threshold(img, new_img, 150, 255, THRESH_BINARY);
    

    Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(15, 15));
    cv::morphologyEx(new_img, new_img, cv::MORPH_OPEN, structuringElement);

    
    return new_img;
}

Mat FiltersClass::watershedFunction(Mat img)
{
    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3, 3) <<
        1, 1, 1,
        1, -8, 1,
        1, 1, 1); // an approximation of second derivative, a quite strong kernel

    Mat imgLaplacian;
    filter2D(img, imgLaplacian, CV_32F, kernel);
    Mat sharp;
    img.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;

    // convert back to 8bits gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 120, 255, THRESH_BINARY);

    Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10));
    cv::morphologyEx(bw, bw, cv::MORPH_OPEN, structuringElement);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    // so we can visualize and threshold it
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);

    // Threshold to obtain the peaks
    // This will be the markers for the foreground objects

    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
    cv::morphologyEx(dist, dist, cv::MORPH_OPEN, structuringElement);

    // Dilate a bit the dist image
    Mat new_kernel = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, new_kernel);

    // Create the CV_8U version of the distance image
    // It is needed for findContours()
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    vector<vector<Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(dist_8u, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Draw the foreground markers
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    // Draw the background marker
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);

    watershed(imgResult, markers);
    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);

    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }
    // Create the result image
    //Mat dst = Mat::zeros(markers.size(), CV_8UC3);
    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i, j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
            {
                img.at<Vec3b>(i, j) = colors[index - 1];
            }
        }
    }

    return img;
}
