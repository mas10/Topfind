#include "Getpicture.h"
#include "ColorExt.h"
#include "Topfind.h"

#include "direct.h"
#include "math.h"
#include <opencv2/opencv.hpp>           //いらない
#include <opencv2/imgcodecs.hpp>        //いらない
#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;     //一部cv::が付いてるのは曖昧回避

int main(void)
{
    Getpicture img("./image/Origami5.JPG");
    // 入力画像表示 "Origami.jpg"　Sankaku
    Mat raw_img;
    resize(img.src_img, raw_img, Size(), 0.25, 0.25);
    cv::imshow("Image", raw_img);

#if 1
    //色抽出
    auto min = Scalar(0, 0, 0);
    auto max = Scalar(164, 72, 255);//BGR 青:200, 120, 100 赤:255, 90, 255 |HSV 赤:255, 110, 255 | 4:255, 70, 255 | 5:255,72,255
    ColorExt ext(raw_img, min, max, 1);//引数4が0以外ならHSVで処理
    cv::imshow("Extracted", ext.eimg);
    //抽出結果をマスク表示
    Mat mask_img;
    raw_img.copyTo(mask_img, ext.eimg);
    cv::imshow("Masked", mask_img);
    //頂点抽出
    Topfind top(ext.eimg, raw_img);
    cv::imshow("Topfind", raw_img);
#else
    //エッジ抽出
    Mat canny_img;
    Canny(raw_img, canny_img, 50, 200);
    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    imshow("Canny", canny_img);

    //ハフ変換
    vector<Vec2f> lines;
    HoughLines(canny_img, lines, 1, CV_PI / 360, 210);

    size_t i = 0, j = 0;
    Mat mat_a(2, 2, CV_8UC1), mat_b(2, 1, CV_32FC1), mat_c(2, 1, CV_32FC1), mat_d(2, 1, CV_32FC1);
    char value_c[256];
    int x = 0;
    while (i < lines.size())
    {
        //線を引く部分
        float theta = lines[i][1];
        float rho = lines[i][0];
        double l = cos(theta), m = sin(theta);
        double x0 = l*rho, y0 = m*rho;
        Point pt1(cvRound(x0 + 1000 * (-m)),
            cvRound(y0 + 1000 * (l)));
        Point pt2(cvRound(x0 - 1000 * (-m)),
            cvRound(y0 - 1000 * (l)));
        line(raw_img, pt1, pt2, CV_RGB(0, 255, 0), 3, 8);
        j = i + 1;
        /*頂点抽出部分*/
        while (j < lines.size())
        {

            float a = lines[i][1];
            float b = lines[j][1];
            float c = lines[i][0];
            float d = lines[j][0];
            mat_a = (cv::Mat_<double>(2, 2) << cos(b), sin(b), cos(a), sin(a));
            mat_b = (cv::Mat_<double>(2, 1) << -c * cos(a) + d * cos(b), -c * sin(a) + d * sin(b));
            std::cout << "mat_a=" << mat_a << ":" << i << "," << j << std::endl << std::endl;
            std::cout << "mat_b=" << mat_b << std::endl << std::endl;
            mat_c = (1 / (sin(a) * cos(b) - cos(a) * sin(b))) * mat_a * mat_b;
            mat_b = (cv::Mat_<double>(2, 1) << sin(a), -cos(a));
            mat_d = (cv::Mat_<double>(2, 1) << c * cos(a), c * sin(a));
            mat_c = mat_c.at<double>(0, 0) * mat_b + mat_d;
            /*画面外ならプロットしないようにする*/
            if (cvRound(mat_c.at<double>(0, 0)) < raw_img.cols && cvRound(mat_c.at<double>(1, 0)) < raw_img.rows)
            {
                x++;
                Point pt(cvRound(mat_c.at<double>(0, 0)), cvRound(mat_c.at<double>(1, 0)));
                circle(raw_img, pt, 10, CV_RGB(0, 0, 255), 3);
                sprintf(value_c, "%d", x);
                putText(raw_img, value_c, pt, FONT_HERSHEY_TRIPLEX, 1.2, CV_RGB(0, 0, 0), 1.2, CV_AA);
            }
            j++;
        }
        i++;
    }
    cv::imshow("Topfind", raw_img);
#endif
    waitKey(0);
}
