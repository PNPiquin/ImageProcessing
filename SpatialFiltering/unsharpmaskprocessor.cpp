#include "unsharpmaskprocessor.h"

UnsharpMaskProcessor::UnsharpMaskProcessor()
{
}

void UnsharpMaskProcessor::ProcessUnsharpMask(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, double unsharp_coeff, bool save_unsharp_mask, int gaussian_filter_size, QProgressBar *progress_bar){
    img_out.resize(img.rows(), img.cols());
    int rows = img_out.rows();
    Eigen::MatrixXi unsharp_mask(img.rows(), img.cols()), blur_img(img.rows(), img.cols());

    GaussianBlurFilter gbf(gaussian_filter_size);
    gbf.ProcessMatrixImg(img, blur_img);

    //unsharp_mask = img - blur_img;
    //IntensityTransformation::ProcessNormalization(unsharp_mask);

    for(int i = 0; i < img_out.rows(); ++i){
      for(int j = 0; j < img_out.cols(); ++j){
        unsharp_mask(i, j) = std::abs(img(i, j) - blur_img(i, j));
      }
      if(progress_bar){
          progress_bar->setValue(std::floor(((i+1)*50)/rows));
      }
    }

    if(save_unsharp_mask){
        JpegManager::SaveGrayscaleMatrixImg(unsharp_mask, "/home/pierre-nicolas/Pictures/ImageProcessing/unsharp_mask");
    }

    // img_out = img + unsharp_coeff * unsharp_mask;
    for(int i = 0; i < img_out.rows(); ++i){
      for(int j = 0; j < img_out.cols(); ++j){
        img_out(i, j) = std::min((int)(img(i, j) + unsharp_coeff * unsharp_mask(i, j)), 255);
      }
      if(progress_bar){
          progress_bar->setValue(std::floor(50 + ((i+1)*50)/rows));
      }
    }
}
