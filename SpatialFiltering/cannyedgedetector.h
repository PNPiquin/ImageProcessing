#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include <Eigen/Dense>
#include <QProgressBar>

class CannyEdgeDetector
{
public:
    CannyEdgeDetector();

    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar = NULL);
    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, QProgressBar *progress_bar = NULL);

private:
    static void ComputeMagAndDirEdgeImg(Eigen::MatrixXi &img, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, QProgressBar *progress_bar = NULL);
};

#endif // CANNYEDGEDETECTOR_H
