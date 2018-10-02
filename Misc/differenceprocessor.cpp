#include "differenceprocessor.h"

// Constructor
DifferenceProcessor::DifferenceProcessor(int step, DifferenceType diff_type) :
    step(step),
    diff_type(diff_type)
{

}

// Main process method
void DifferenceProcessor::ProcessDifference(std::vector<std::shared_ptr<ImageHolder>> img_vect,
        std::vector<std::shared_ptr<ImageHolder>> *out_vect,
        std::string output_suffix,
        ProgressLogger *progress_logger){
    const unsigned int img_vect_size = img_vect.size();

    // progress logger init
    if(progress_logger){
        progress_logger->SetTaskNumber(img_vect_size - step);
        progress_logger->SetIsProcessing(true);
    }

    // Make sure that the out vector is empty before processing
    out_vect->clear();

    for(unsigned int i = step; i < img_vect_size; ++i){
        out_vect->push_back(ProcessImageDifference(
                                img_vect.at(i),
                                img_vect.at(i - step),
                                img_vect.at(i)->GetImageName() + output_suffix));

        if(progress_logger){
            progress_logger->IncrementFinishedTasksCpt();
        }
    }

    if(progress_logger){
        progress_logger->SetIsProcessing(false);
    }
}

// Utils methods
std::shared_ptr<ImageHolder> DifferenceProcessor::ProcessImageDifference(
        std::shared_ptr<ImageHolder> img_in,
        std::shared_ptr<ImageHolder> back_img,
        std::string output_name){
    // Params
    const int rows = img_in->mat_img.rows();
    const int cols = img_in->mat_img.cols();

    // New image initialisation
    Eigen::MatrixXi img_out;
    img_out.resize(rows, cols);

    // Difference processing
    switch(diff_type){
        case DifferenceType::POSITIVE:
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                    img_out(i, j) = std::max(0, img_in->mat_img(i, j) - back_img->mat_img(i, j));
                }
            }
            break;
        case DifferenceType::NEGATIVE:
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                    img_out(i, j) = std::max(0, back_img->mat_img(i, j) - img_in->mat_img(i, j));
                }
            }
            break;
        case DifferenceType::ABS:
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j){
                    img_out(i, j) = std::abs(img_in->mat_img(i, j) - back_img->mat_img(i, j));
                }
            }
            break;
    }

    return std::make_shared<ImageHolder>(img_out, output_name, ImageHolder::ImageType::GRAYSCALE);
}
