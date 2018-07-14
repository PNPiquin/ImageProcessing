#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include <Eigen/Dense>
#include <QProgressBar>

#include "ProgressLogger/progresslogger.h"

class CannyEdgeDetector
{
public:
    CannyEdgeDetector();

    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger = NULL);
    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, ProgressLogger *progress_logger = NULL);

private:
    static void ComputeMagAndDirEdgeImg(Eigen::MatrixXi &img, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, ProgressLogger *progress_logger = NULL);
};

#endif // CANNYEDGEDETECTOR_H
