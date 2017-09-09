#include "HistogramProcessor.h"

const int HistogramProcessor::value_range = 256;

HistogramProcessor::HistogramProcessor(){
  for (int i = 0; i < value_range; ++i) {
    histogram.insert(std::pair<int, double>(i, 0.0));
    inverse_histogram.insert(std::pair<int, double>(i, 0.0));
  }
}

void HistogramProcessor::HistogramInit(Eigen::MatrixXi &img){
  int rows = img.rows();
  int cols = img.cols();
  double size_inverse = 1.0 / (std::max(1, rows * cols));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      histogram.at(img(i, j)) += size_inverse;
    }
  }
  for(int i = 0; i < value_range; ++i){
    double s_i(0.0);
    for(int j = 0; j <= i; ++j){
      s_i += histogram.at(j);
    }
    inverse_histogram.at(i) = (s_i * (double)value_range);
  }
}

void HistogramProcessor::ProcessEqualization(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, QProgressBar *progress_bar){
  HistogramInit(img);
  int rows = img.rows();
  int cols = img.cols();
  imgOut.resize(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int value = std::floor(inverse_histogram.at(img(i, j)) + 0.5);
      imgOut(i, j) = std::min(255, value);
    }
    if(progress_bar){
        progress_bar->setValue(std::floor(((i+1)*100)/rows));
    }
  }
}
