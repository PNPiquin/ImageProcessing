#ifndef INTENSITY_TRANSFORMATION_H
#define INTENSITY_TRANSFORMATION_H

#include <Eigen/Dense>
#include <QProgressBar>
#include "ProgressLogger/progresslogger.h"

class IntensityTransformation {
public:
  IntensityTransformation();

  static void ProcessPowerLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double gamma = 1.0, double c = 1.0, ProgressLogger *progress_logger=NULL);
  static void ProcessLogLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double c = 1.0, ProgressLogger *progress_logger=NULL);
  static void ProcessThresholding(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, int threshold = 128, ProgressLogger *progress_logger=NULL);
  static void ProcessNormalization(Eigen::MatrixXi &imgOut, int value_max = 255, ProgressLogger *progress_logger=NULL);
  static void ProcessTransformation(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, std::function<int(int)> transformation, ProgressLogger *progress_logger=NULL);
  static void ProcessNegative(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, ProgressLogger *progress_logger=NULL);

};

#endif
