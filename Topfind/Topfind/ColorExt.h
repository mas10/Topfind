#include "Errors.h"

using namespace std;
using namespace cv;

class ColorExt
{
public:
    Mat eimg;

    ColorExt();
    ColorExt(Mat src, Scalar min, Scalar max, int mode);
    ~ColorExt();
};

