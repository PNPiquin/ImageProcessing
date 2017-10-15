#include "IntensityTransformation.h"

IntensityTransformation::IntensityTransformation(){

}

void IntensityTransformation::ProcessPowerLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double gamma, double c, QProgressBar *progress_bar){
  ProcessTransformation(
  img,
  imgOut,
  [&](int value) {return std::floor(0.5 + c * std::pow(value, gamma));},
  progress_bar
  );
  ProcessNormalization(imgOut);
}

void IntensityTransformation::ProcessLogLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double c, QProgressBar *progress_bar){
  ProcessTransformation(
  img,
  imgOut,
  [&](int value) {return std::floor(0.5 + c * std::log(1 + value));},
  progress_bar
  );
  ProcessNormalization(imgOut);
}

void IntensityTransformation::ProcessThresholding(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, int threshold, QProgressBar *progress_bar){
    ProcessTransformation(
    img,
    imgOut,
    [&](int value) {return value > threshold ? 255 : 0;},
    progress_bar
    );
}

void IntensityTransformation::ProcessNormalization(Eigen::MatrixXi &imgOut, int value_max, QProgressBar *progress_bar){
  int max = 0;
  int rows = imgOut.rows();
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      if(imgOut(i, j) > max){
        max = imgOut(i, j);
      }
      if(progress_bar){
          progress_bar->setValue(std::floor(((i+1)*50)/rows));
      }
    }
  }
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      imgOut(i, j) = std::floor(value_max * imgOut(i, j) / max);
    }
    if(progress_bar){
        progress_bar->setValue(std::floor(50 + ((i+1)*50)/rows));
    }
  }
}

void IntensityTransformation::ProcessTransformation(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, std::function<int(int)> transformation, QProgressBar *progress_bar){
  imgOut.resize(img.rows(), img.cols());
  int rows = imgOut.rows();
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      imgOut(i, j) = transformation(img(i, j));
    }
    if(progress_bar){
        progress_bar->setValue(std::floor(((i+1)*100)/rows));
    }
  }
}

void IntensityTransformation::ProcessNegative(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, QProgressBar *progress_bar){
    ProcessTransformation(
    img,
    imgOut,
    [&](int value) {return 255 - value;},
    progress_bar
    );
}
