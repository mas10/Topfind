#include "Libs.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class Errors
{
    const char *msg;
public:
    Errors();
    ~Errors();
    Errors(const char *);

};

