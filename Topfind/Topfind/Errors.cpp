#include "Errors.h"


using namespace std;
using namespace cv;

//Error‚ð•\Ž¦‚·‚é
Errors::Errors()
{
}

Errors::~Errors()
{
}

//Error:code‚ð•\Ž¦‚·‚é
Errors::Errors(const char *m)
{
    msg = m;
    Mat error_img(Size(640, 480), CV_8UC3, Scalar(100, 100, 100));
    putText(error_img, msg, Point(0, 240), FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 0, 0), 1.2, CV_AA);
    namedWindow("Error", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    imshow("Error", error_img);
    waitKey(0);
}


