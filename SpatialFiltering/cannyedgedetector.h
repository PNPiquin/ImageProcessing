#ifndef CANNYEDGEDETECTOR_H
#define CANNYEDGEDETECTOR_H

#include <Eigen/Dense>

class CannyEdgeDetector
{
public:
    CannyEdgeDetector();

    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out);
    static void ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir);

private:
    static void ComputeMagAndDirEdgeImg(Eigen::MatrixXi &img, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir);
};

#endif // CANNYEDGEDETECTOR_H
