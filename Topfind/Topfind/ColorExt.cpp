#include "ColorExt.h"

ColorExt::ColorExt()
{
}


ColorExt::ColorExt(Mat src, Scalar min, Scalar max, int mode)
{
    if (mode == 0) eimg = src;
    if (mode != 0) cv::cvtColor(src, eimg, CV_RGB2HSV, 3);
    cv::GaussianBlur(eimg, eimg, Size(9, 7), 3.05, 2.45);
    cv::inRange(eimg, min, max, eimg);
    if (mode != 0) cv::bitwise_not(eimg, eimg);
}

ColorExt::~ColorExt()
{
}
