#include "Getpicture.h"
#include "direct.h"
#include "math.h"
#include <opencv2/opencv.hpp>           //����Ȃ�
#include <opencv2/imgcodecs.hpp>        //����Ȃ�
#include <opencv2/highgui/highgui.hpp>  //����Ȃ�
#include <iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(void)
{
    Getpicture img("./image/Origami.jpg");
    // ���͉摜�\�� "Origami.jpg"
    Mat raw_image;
    namedWindow("Image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    resize(img.src_img, raw_image, Size(), 0.25, 0.25);
    imshow("Image", raw_image);

    //�G�b�W���o
    Mat canny_img;
    Canny(raw_image, canny_img, 50, 200);
    namedWindow("Canny", CV_WINDOW_AUTOSIZE);
    imshow("Canny", canny_img);

    //�n�t�ϊ�
#if 1
    vector<Vec2f> lines;
    HoughLines(canny_img, lines, 1, CV_PI / 180, 154);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        Point pt1(cvRound(x0 + 1000 * (-b)),
            cvRound(y0 + 1000 * (a)));
        Point pt2(cvRound(x0 - 1000 * (-b)),
            cvRound(y0 - 1000 * (a)));
        line(raw_image, pt1, pt2, Scalar(0, 255, 0), 3, 8);
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
