#ifndef COMMON_SPATIAL_FILTERS_H
#define COMMON_SPATIAL_FILTERS_H

#include <Eigen/Dense>
#include "SpatialFilter.h"

class EdgeDetectionFilter : public SpatialFilter {
public:
  EdgeDetectionFilter();
  EdgeDetectionFilter(int filter_size);
  void Create3X3Filter();
  void Create5X5Filter();
};

class GaussianBlurFilter : public SpatialFilter {
public:
  GaussianBlurFilter();
  GaussianBlurFilter(int filter_size);
  void Create3X3Filter();
  void Create5X5Filter();
  void CreateNXNFilter(int n);
};

#endif
