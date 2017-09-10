#include "CommonSpatialFilters.h"

// Edge Detection Filter

EdgeDetectionFilter::EdgeDetectionFilter() : SpatialFilter(){
}

EdgeDetectionFilter::EdgeDetectionFilter(int filter_size) : SpatialFilter(){
    switch(filter_size){
    case 3:
        Create3X3Filter();
        break;
    case 5:
        Create5X5Filter();
        break;
    }
}

void EdgeDetectionFilter::Create3X3Filter(){
  Eigen::MatrixXf filter(3, 3);
  filter << -0.125, -0.125, -0.125,
            -0.125,   1,    -0.125,
            -0.125, -0.125, -0.125;
  SetFilter(filter);
}

void EdgeDetectionFilter::Create5X5Filter(){
  Eigen::MatrixXf filter(5, 5);
  filter << -1, -1, -1, -1, -1,
            -1, -2, -2, -2, -1,
            -1, -2, 32, -2, -1,
            -1, -2, -2, -2, -1,
            -1, -1, -1, -1, -1;
  filter *= (1.0 / 32.0);
  SetFilter(filter);
}

// Gaussian Blur Filter

GaussianBlurFilter::GaussianBlurFilter() : SpatialFilter(){
}

GaussianBlurFilter::GaussianBlurFilter(int filter_size) : SpatialFilter(){
    if(filter_size == 3){
        Create3X3Filter();
    }
    else if(filter_size == 5){
        Create3X3Filter();
    }
    else{
        CreateNXNFilter(filter_size);
    }
}

void GaussianBlurFilter::Create3X3Filter(){
  Eigen::MatrixXf filter(3, 3);
  filter << 1, 1, 1,
            1, 1, 1,
            1, 1, 1;
  filter *= (1.0 / 9.0);
  SetFilter(filter);
}

void GaussianBlurFilter::Create5X5Filter(){
  Eigen::MatrixXf filter(5, 5);
  filter << 2, 4, 5, 4, 2,
            4, 9, 12, 9, 4,
            5, 12, 15, 12, 5,
            4, 9, 12, 9, 4,
            2, 4, 5, 4, 2;
  filter *= (1.0 / 159.0);
  SetFilter(filter);
}

void GaussianBlurFilter::CreateNXNFilter(int n){
    if(n % 2 == 1){
        Eigen::MatrixXf filter(n, n);
        int filter_width = (n-1)/2;
        double coeff(0.0);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                int pow = 2 * filter_width - std::abs(i - filter_width) - std::abs(j - filter_width);
                int val = std::pow(2, pow);
                filter(i, j) = val;
                coeff += val;
            }
        }
        filter *= (1.0/coeff);
        SetFilter(filter);
    } else {
        printf("Warning : %i is not an odd integer.", n);
    }
}

// Sobel Filter

SobelFilter::SobelFilter() : SpatialFilter(){
}

void SobelFilter::PopulateHorizontalFilter(){
    Eigen::MatrixXf filter(3, 3);
    filter << -1, -2, -1,
                    0, 0, 0,
                    1, 2, 1;
    SetFilter(filter);
}

void SobelFilter::PopulateVerticalFilter(){
    Eigen::MatrixXf filter(3, 3);
    filter << -1, 0, 1,
                    -2, 0, 2,
                    -1, 0, 1;
    SetFilter(filter);
}
