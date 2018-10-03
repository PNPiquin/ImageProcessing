#include "morphgradient.h"

MorphGradient::MorphGradient(int _size)
{
    size = std::max(_size, 2);
}

void MorphGradient::ProcessVGradient(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger){
    int rows = img.rows();
    int cols = img.cols();
    img_out.resize(rows, cols);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols - size; ++j){
            std::vector<int> data;
            for(int k = 0; k < size; ++k){
                data.push_back(img(i, j+k));
            }
            std::sort(data.begin(), data.end());
            img_out(i, j) = data.back() - data.front();
        }
        if(progress_logger){
            progress_logger->SetProgress(std::floor(((i+1)*100)/(rows)));
        }
    }
}

void MorphGradient::ProcessHGradient(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger){
    int rows = img.rows();
    int cols = img.cols();
    img_out.resize(rows, cols);
    for(int j = 0; j < cols; ++j){
        for(int i = 0; i < rows - size; ++i){
            std::vector<int> data;
            for(int k = 0; k < size; ++k){
                data.push_back(img(i+k, j));
            }
            std::sort(data.begin(), data.end());
            img_out(i, j) = data.back() - data.front();
        }
        if(progress_logger){
            progress_logger->SetProgress(std::floor(((j+1)*100)/(cols)));
        }
    }
}
