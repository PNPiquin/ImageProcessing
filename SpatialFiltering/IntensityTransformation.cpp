#include "IntensityTransformation.h"

IntensityTransformation::IntensityTransformation(){

}

void IntensityTransformation::ProcessPowerLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double gamma, double c){
  ProcessTransformation(
  img,
  imgOut,
  [&](int value) {return std::floor(0.5 + c * std::pow(value, gamma));}
  );
  ProcessNormalization(imgOut);
}

void IntensityTransformation::ProcessLogLaw(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, double c){
  ProcessTransformation(
  img,
  imgOut,
  [&](int value) {return std::floor(0.5 + c * std::log(1 + value));}
  );
  ProcessNormalization(imgOut);
}

void IntensityTransformation::ProcessThresholding(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, int threshold){
    ProcessTransformation(
    img,
    imgOut,
    [&](int value) {return value > threshold ? 255 : 0;}
    );
}

void IntensityTransformation::ProcessNormalization(Eigen::MatrixXi &imgOut, int value_max){
  int max = 0;
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      if(imgOut(i, j) > max){
        max = imgOut(i, j);
      }
    }
  }
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      imgOut(i, j) = std::floor(value_max * imgOut(i, j) / max);
    }
  }
}

void IntensityTransformation::ProcessTransformation(Eigen::MatrixXi &img, Eigen::MatrixXi &imgOut, std::function<int(int)> transformation){
  imgOut.resize(img.rows(), img.cols());
  for(int i = 0; i < imgOut.rows(); ++i){
    for(int j = 0; j < imgOut.cols(); ++j){
      imgOut(i, j) = transformation(img(i, j));
    }
  }
}
