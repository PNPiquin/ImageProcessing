#ifndef SPATIAL_FILTER_H
#define SPATIAL_FILTER_H

#include <iostream>
#include <Eigen/Dense>
#include <QProgressBar>
#include "ProgressLogger/progresslogger.h"


class SpatialFilter {
public:
  SpatialFilter();
  void SetFilter(Eigen::MatrixXf _filter);
  void ProcessMatrixImg(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, ProgressLogger *progress_logger = NULL);

private:
  int size;
  Eigen::MatrixXf filter;

  void ProcessConvolution(int i, int j, Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut);
};

#endif
