#include "resizeprocessor.h"

// Constructor
ResizeProcessor::ResizeProcessor(int x0, int y0, int x1, int y1) :
    x0(x0),
    y0(y0),
    x1(x1),
    y1(y1)
{

}

// Main process function
void ResizeProcessor::ProcessImageResize(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, ProgressLogger *progress_logger){
    // input image dimensions
    const int in_rows = img.rows();
    const int in_cols = img.cols();

    // Checking inputs
    if(x0 < 0 || y0 < 0){
        if(x0 < 0){
            x0 = 0;
        }
        if(y0 < 0){
            y0 = 0;
        }
    }
    if(x1 >= in_rows || y1 >= in_cols ){
        if(x1 >= in_rows){
            x1 = in_rows - 1;
        }
        if(y1 >= in_cols){
            y1 = in_cols - 1;
        }
    }

    // output image dimensions
    const int out_rows = x1 - x0;
    const int out_cols = y1 - y0;

    // checking params validity
    if(out_cols < 1 || out_rows < 1){
        std::cout << "Invalid resize processor parameters" << std::endl;
        return;
    }

    img_out.resize(out_rows, out_cols);

    for(int i = 0; i < out_rows; ++i){
        for(int j = 0; j < out_cols; ++j){
            img_out(i, j) = img(x0 + i, y0 + j);
        }
        if(progress_logger){
            progress_logger->SetProgress(std::floor(((i+1)*100)/out_rows));
        }
    }
}
