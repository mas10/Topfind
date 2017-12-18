#include "Topfind.h"



Topfind::Topfind()
{
}

Topfind::Topfind(Mat src, Mat rezult)
{
    //エッジ抽出
    vector<vector<Point>> contours;
    vector<Point> approx;
    cv::findContours(src, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    cv::drawContours(rezult, contours, -1, CV_RGB(0, 0, 255), 3, 8);
    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), approx, 0.01 * arcLength(contours[i], true), true);
    }
    //頂点抽出
    char value_c[256];
    for (int i = 0; i < approx.size(); i++) {
        if (approx[i].x >= rezult.cols - 1 || approx[i].y >= rezult.rows - 1) continue;
        Point pt(approx[i].x, approx[i].y);
        circle(rezult, pt, 10, CV_RGB(255, 0, 0), 3);
        sprintf(value_c, "%d", i + 1);
        putText(rezult, value_c, pt, FONT_HERSHEY_TRIPLEX, 1.2, CV_RGB(0, 0, 0), 1.2, CV_AA);
    }
}


Topfind::~Topfind()
{
}
