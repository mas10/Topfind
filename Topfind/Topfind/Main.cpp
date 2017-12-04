#include "Getpicture.h"
#include "direct.h"
#include "math.h"
#include <opencv2/opencv.hpp>           //いらない
#include <opencv2/imgcodecs.hpp>        //いらない
#include <opencv2/highgui/highgui.hpp>  //いらない
#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(void)
{
    Getpicture img("./image/Origami.jpg");
    // 入力画像表示 "Origami.jpg"
    Mat raw_image;
    namedWindow("Image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    resize(img.src_img, raw_image, Size(), 0.25, 0.25);
    imshow("Image", raw_image);

    //エッジ抽出
    Mat canny_img;
    Canny(raw_image, canny_img, 50, 200);
    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    imshow("Canny", canny_img);

    //ハフ変換
#if 1
    vector<Vec2f> lines;
    HoughLines(canny_img, lines, 1, CV_PI / 180, 154);
    
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
        line(raw_image, pt1, pt2, Scalar(0, 255, 0), 3, 8);
        j = i + 1;
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
            Point pt(cvRound(mat_c.at<double>(0, 0)), cvRound(mat_c.at<double>(1, 0)));
            circle(raw_image, pt, 10, CV_RGB(0, 0, 255), 3);/*画面外ならプロットしないようにする*/
            sprintf(value_c, "%d", x++);
            putText(raw_image, value_c, pt , FONT_HERSHEY_TRIPLEX, 1.2, Scalar(0, 255, 0), 1.2, CV_AA);
            j++;
            
        }
        i++;
    }
    
#else
    vector<Vec4i> lines;
    HoughLinesP(canny_img, lines, 1, CV_PI / 180, 80, 30, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        line(raw_image, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 3, 8);
    }
#endif

    namedWindow("Detected Lines", 1);
    imshow("Detected Lines", raw_image);

    waitKey(0);
}
