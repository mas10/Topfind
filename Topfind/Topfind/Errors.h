#include "Libs.h"
#include <opencv2/opencv.hpp>

class Errors
{
    const char *msg;
public:
    Errors();
    ~Errors();
    Errors(const char *);

};

