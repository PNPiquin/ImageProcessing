#include "cannyedgedetector.h"
#include "CommonSpatialFilters.h"
#include "IntensityTransformation.h"
#include "../IO/JpegManager.h"

CannyEdgeDetector::CannyEdgeDetector()
{

}

void CannyEdgeDetector::ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar){
    Eigen::MatrixXi mag;
    Eigen::MatrixXf dir;
    CannyEdgeDetector::ProcessCannyEdgeDetector(img, img_out, mag, dir, progress_bar);
}

void CannyEdgeDetector::ProcessCannyEdgeDetector(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, QProgressBar *progress_bar){
    int rows = img.rows();
    int cols = img.cols();
    int filter_size = 5;
    int padding = (filter_size - 1) / 2;
    int threshold(20);

    // ProgressBar resizing
    if(progress_bar){
        progress_bar->setRange(0, 400);
    }

    // Resizing the matrix to the img size
    img_out.resize(rows, cols);
    mag.resize(rows, cols);
    dir.resize(rows, cols);

    // First, we need a blurred version of img
    Eigen::MatrixXi blurred_img(rows, cols);
    GaussianBlurFilter gbf(filter_size);
    gbf.ProcessMatrixImg(img, blurred_img, progress_bar);

    // Then, we need to populate the mag and the dir imgs
    ComputeMagAndDirEdgeImg(blurred_img, mag, dir, progress_bar);

    // Need to classify all point by their "edge direction" to keep or to suppress
    double PI(3.141592653589793238462);
    for(int i = padding; i < rows - padding; ++i){
        for(int j = padding; j < cols - padding; ++j){
            double alpha = dir(i, j);
            if((alpha < (PI / 8.0)) && (alpha > (-PI/8.0))){
                if( (mag(i, j) < mag(i, j-1)) || (mag(i, j) < mag(i, j+1)) ){
                    img_out(i, j) = 0;
                }
                else{
                    img_out(i, j) = mag(i, j);
                }
            }
            else if((alpha < (3*PI / 8.0)) && (alpha > (PI/8.0))){
                if( (mag(i, j) < mag(i-1, j-1)) || (mag(i, j) < mag(i+1, j+1)) ){
                    img_out(i, j) = 0;
                }
                else{
                    img_out(i, j) = mag(i, j);
                }
            }
            else if((alpha < (-PI / 8.0)) && (alpha > (-3*PI/8.0))){
                if( (mag(i, j) < mag(i+1, j-1)) || (mag(i, j) < mag(i-1, j+1)) ){
                    img_out(i, j) = 0;
                }
                else{
                    img_out(i, j) = mag(i, j);
                }
            }
            else{
                if( (mag(i, j) < mag(i+1, j)) || (mag(i, j) < mag(i-1, j)) ){
                    img_out(i, j) = 0;
                }
                else{
                    img_out(i, j) = mag(i, j);
                }
            }
        }
        if(progress_bar){
            progress_bar->setValue(200 + std::floor(((i+1)*100)/rows));
        }
    }

    // Last thing to do --> Threshold

    // Second version of thresholding for Canny
#if 0
    int low_threshold(10), high_threshold(40);
    Eigen::MatrixXi low_img(rows, cols), high_img(rows, cols);
    IntensityTransformation::ProcessThresholding(img_out, low_img, low_threshold, progress_bar);
    IntensityTransformation::ProcessThresholding(img_out, high_img, high_threshold, progress_bar);
    JpegManager::SaveGrayscaleMatrixImg(low_img, "/home/pierre-nicolas/Pictures/ImageProcessing/Canny/low_mag");
    JpegManager::SaveGrayscaleMatrixImg(high_img, "/home/pierre-nicolas/Pictures/ImageProcessing/Canny/high_mag");
#endif

    // This first version is very basic
    if(progress_bar){
        progress_bar->setRange(-300, 100);
        progress_bar->setValue(0);
    }
    IntensityTransformation::ProcessThresholding(img_out, img_out, threshold, progress_bar);

    if(progress_bar){
        progress_bar->setRange(0, 100);
    }

}

void CannyEdgeDetector::ComputeMagAndDirEdgeImg(Eigen::MatrixXi &img, Eigen::MatrixXi &mag, Eigen::MatrixXf &dir, QProgressBar *progress_bar){
    // For now the filter size is set to 3 to use Sobel filters
    int rows = img.rows();
    int cols = img.cols();
    int filter_size = 3;
    int padding = (filter_size - 1) / 2;

    Eigen::MatrixXf filter_x(3, 3);
    filter_x << -1, -2, -1,
                    0, 0, 0,
                    1, 2, 1;

    Eigen::MatrixXf filter_y(3, 3);
    filter_y << -1, 0, 1,
                    -2, 0, 2,
                    -1, 0, 1;

    // Convolution method
    auto convolution = [&filter_x, &filter_y, padding, &img](int i, int j, double &gx, double &gy){
        double convolution_result_x(0.0), convolution_result_y(0.0);
        for(int l = i - padding; l <= i + padding; ++l){
          for(int k = j - padding; k <= j + padding; ++k){
              convolution_result_x += filter_x(l - (i - padding), k - (j - padding)) * img(l, k);
              convolution_result_y += filter_y(l - (i - padding), k - (j - padding)) * img(l, k);
          }
        }
        gx = convolution_result_x;
        gy = convolution_result_y;
    };

    // Compute gx and gy
    for(int i = padding; i < rows - padding; ++i){
        for(int j = padding; j < cols - padding; ++j){
            double gx(0.0), gy(0.0);
            convolution(i, j, gx, gy);
            mag(i, j) = std::floor(std::sqrt( std::pow(gx, 2) + std::pow(gy, 2)) + 0.5);
            dir(i, j) = std::atan( gy == 0.0 ? (gx / gy) : (1000 * gx) );
        }
        if(progress_bar){
            progress_bar->setValue(100 + std::floor(((i+1)*100)/(rows-padding)));
        }
    }

}
