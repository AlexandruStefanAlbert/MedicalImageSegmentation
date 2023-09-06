#include "Filters.h"
#include "MyLabel.h"

FiltersClass::FiltersClass()
{
		
}
FiltersClass::~FiltersClass()
{
	
}
/// <summary>
/// Conversia unei imagini sub forma unui obiect QImage intr-un obiect de tipul Mat din librarira OpenCV
/// </summary>
/// <param name="img"></param>
/// <returns>O imagine Mat</returns>
Mat FiltersClass::convertQImageToMat(QImage &img)
{
	img = img.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
	return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}
/// <summary>
/// Conversia unui imagini sub forma de obiect Mat intr-un obiect QImage din libraria QT
/// </summary>
/// <param name="inMat"></param>
/// <returns>O imagine QImage</returns>
QImage  FiltersClass::convertMatToQImage(const cv::Mat& inMat)
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

/// <summary>
/// Imbunatatirea calitatii imaginii, ajustarea constrastului, luminozitatii, factorului gamma
/// </summary>
/// <param name="img"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="gamma"></param>
/// <returns>O imagine imbunatatita astfel incat sa se realizeze segmentarea sau sa se evidentieze anumite zone de interes</returns>
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
/// <summary>
/// Reducerea zgomotului aplicand un filtru de Median Blur
/// </summary>
/// <param name="img"></param>
/// <returns>Imaginea imbunatatita dupa aplicarea filtrului de Median Blur</returns>
Mat FiltersClass::noiseReduceMedian(Mat img)
{
    Mat new_img = Mat::zeros(img.size(), img.type());

    medianBlur(img, new_img, 5);

    return new_img;


}
/// <summary>
/// Reducerea zgomotului aplicand un filtru Gaussian
/// </summary>
/// <param name="img"></param>
/// <returns>Imaginea imbunatatita dupa aplicarea filtrului Gaussian</returns>
Mat FiltersClass::noiseReduceGaussian(Mat img)
{
    Mat new_img = Mat::zeros(img.size(), img.type());

    GaussianBlur(img, new_img, Size(5, 5),1.0);

    return new_img;
}
/// <summary>
/// Segmentarea imaginii pentru extragerea tumorii
/// </summary>
/// <param name="img"></param>
/// <returns>O imagine binarizata ce reprezinta masca tumorii</returns>
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
    
    //Matricea kernel pentru filtrul laplacian pentru a determina muchiile imaginii
    Mat kernel = (Mat_<float>(3, 3) <<
        1, 1, 1,
        1, -8, 1,
        1, 1, 1);

    Mat imgLaplacian;
    filter2D(img, imgLaplacian, CV_32F, kernel);
    Mat sharp;
    img.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;

    // convertire in grayscale 8bits
    imgResult.convertTo(imgResult, CV_8UC3);
    //imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    // Crearea unei imagini binare pe baza imaginii încărcate
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 120, 255, THRESH_BINARY);
    //Aplicarea unei operatii morfologice de deschidere
    Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10));
    cv::morphologyEx(bw, bw, cv::MORPH_OPEN, structuringElement);

    // Aplicarea Transformatei distanta asupra imaginii binare
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalizare in range-ul = [0.0, 1.0]
 
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);

    // Threshold pentru a obtine "varfurile" imaginii + operatie morfologică

    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
    cv::morphologyEx(dist, dist, cv::MORPH_OPEN, structuringElement);

    // Dilatarea imaginii transformatei distanta
    Mat new_kernel = Mat::ones(3, 3, CV_8U);
    cv::dilate(dist, dist, new_kernel);

    //Marcarea obiectelor pt algoritmul Watershed
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);
    vector<vector<Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    findContours(dist_8u, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // Crearea marker-elor
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Desenarea obiectelor marker
    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    // Desenarea fundalului marker
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    /*Mat markers8u;
    markers.convertTo(markers8u, CV_8U, 10);*/

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
     
    // Umplerea obiectelor de culori
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
