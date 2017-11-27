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
    src_img = imread(p, CV_LOAD_IMAGE_COLOR);
    // ‰æ‘œ‚ª“Ç‚İ‚Ü‚ê‚È‚©‚Á‚½‚çƒvƒƒOƒ‰ƒ€I—¹
    if (src_img.empty())
    {
        Errors("Error:src_img is empty.");
        exit(0);
    }
}
