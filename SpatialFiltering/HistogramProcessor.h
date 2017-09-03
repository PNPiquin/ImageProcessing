#ifndef HISTOGRAM_PROCESSOR_H
#define HISTOGRAM_PROCESSOR_H

#include <map>
#include <Eigen/Dense>

class HistogramProcessor{
public:
  HistogramProcessor();
  void ProcessEqualization(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut);
  void HistogramInit(Eigen::MatrixXi &img);

private:
  std::map<int, double> histogram;
  std::map<int, double> inverse_histogram;

  static const int value_range;
};

#endif
