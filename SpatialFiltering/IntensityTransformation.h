#ifndef INTENSITY_TRANSFORMATION_H
#define INTENSITY_TRANSFORMATION_H

#include <Eigen/Dense>

class IntensityTransformation {
public:
  IntensityTransformation();

  static void ProcessPowerLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double gamma = 1.0, double c = 1.0);
  static void ProcessLogLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double c = 1.0);
  static void ProcessThresholding(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, int threshold = 128);
  static void ProcessNormalization(Eigen::MatrixXi &imgOut, int value_max = 255);
  static void ProcessTransformation(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, std::function<int(int)> transformation);

};

#endif
