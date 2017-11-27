#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class Getpicture
{
    const char *path;
public:
    Mat src_img;

    Getpicture();
    ~Getpicture();
    Getpicture(const char *);
};

