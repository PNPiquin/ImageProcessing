#ifndef MORPHGRADIENT_H
#define MORPHGRADIENT_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "ProgressLogger/progresslogger.h"

class MorphGradient
{
public:
    MorphGradient(int _size = 2);

    void ProcessVGradient(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger=NULL);
    void ProcessHGradient(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger=NULL);

private:
    int size;
};

#endif // MORPHGRADIENT_H
