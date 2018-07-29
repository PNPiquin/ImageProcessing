#ifndef RESIZEPROCESSOR_H
#define RESIZEPROCESSOR_H

// Standard includes
#include <iostream>

// third party libraries
#include <Eigen/Dense>

// project
#include "ProgressLogger/progresslogger.h"

class ResizeProcessor
{
public:
    ResizeProcessor(int x0, int y0, int x1, int y1);

    void ProcessImageResize(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger = NULL);

private:
    int x0, y0, x1, y1;
};

#endif // RESIZEPROCESSOR_H
