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
    // �摜���ǂݍ��܂�Ȃ�������v���O�����I��
    if (src_img.empty())
    {
        Errors("Error:src_img is empty.");
        exit(0);
    }
}
