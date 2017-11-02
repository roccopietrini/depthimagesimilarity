#include <QCoreApplication>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <QDebug>

using namespace std;
double getSimilarity(const cv::Mat A, const cv::Mat B);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::Mat model, old_model;
    model = cv::imread(argv[1],CV_LOAD_IMAGE_ANYDEPTH);
    old_model = cv::imread(argv[2],CV_LOAD_IMAGE_ANYDEPTH);

    if( argc != 3)
    {
     cout <<" Error! No images provided! Usage: modelmatcher <image1> <image2>" << endl;
     return -1;
    }

    if((!model.data) || (!old_model.data))      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

//    unsigned short x = model.at<unsigned short>(cv::Point(200,120));
//    cout << "value: " << x << endl;
//    qDebug() << model.at<unsigned short>(cv::Point(200,120));
    cout << "Similarity per pixel: " << getSimilarity(model,old_model) << endl;
    return a.exec();
}

// Compare two images by getting the L2 error (square-root of sum of squared error).
double getSimilarity( const cv::Mat A, const cv::Mat B )
{
    if ( A.rows > 0 && A.rows == B.rows && A.cols > 0 && A.cols == B.cols )
    {
        // Calculate the L2 relative error between images.
        double errorL2 = cv::norm( A, B, CV_L2 );
        cout << "Total L2 error: " << errorL2 << endl;
        double errorL2_matA = cv::norm(A,CV_L2);
        cout << "Max: " << errorL2_matA << endl; //Max is when the second matrix is 0
        double percentage = (errorL2*100)/errorL2_matA;
        cout << "Percentage: " << (int)percentage << endl;
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double)( A.rows * A.cols );
        return similarity;
    }
    else
    {
        //Images have a different size
        return 100000000.0;  // Return a bad value
    }
}
