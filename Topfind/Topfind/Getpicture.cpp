#include "Getpicture.h"
#include "Errors.h"


using namespace std;
using namespace cv;

Getpicture::Getpicture()
{
}


Getpicture::~Getpicture()
{
}

Getpicture::Getpicture(const char *p)
{
    path = p;
    src_img = imread(p, 1);
    // 画像が読み込まれなかったらプログラム終了
    if (src_img.empty())
    {
        Errors("Error:src_img is empty.");
        exit(0);
    }
}
