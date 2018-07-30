#include "SpatialFilter.h"

SpatialFilter::SpatialFilter(){

}

void SpatialFilter::SetFilter(Eigen::MatrixXf _filter){
  size = _filter.rows();
  filter = _filter;
}

void SpatialFilter::ProcessMatrixImg(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, ProgressLogger *progress_logger){
  int rows = img.rows();
  int cols = img.cols();
  int padding = (size - 1) / 2;
  imgOut.resize(rows, cols);
  for(int i = padding; i < rows - padding; ++i){
    for(int j = padding; j < cols - padding; ++j){
      ProcessConvolution(i, j, img, imgOut);
    }
    if(progress_logger){
        progress_logger->SetProgress(std::floor(((i+1)*100)/(rows-padding)));
    }
  }
}

void SpatialFilter::ProcessConvolution(int i, int j, Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut){
  int padding = (size - 1) / 2;
  double convolution_result(0.0);
  for(int l = i - padding; l <= i + padding; ++l){
    for(int k = j - padding; k <= j + padding; ++k){
      convolution_result += filter(l - (i - padding), k - (j - padding)) * img(l, k);
    }
  }
  imgOut(i, j) = static_cast<int>(convolution_result);
}
