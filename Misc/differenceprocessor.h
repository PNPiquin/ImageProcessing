#ifndef DIFFERENCEPROCESSOR_H
#define DIFFERENCEPROCESSOR_H

// third party libraries
#include <Eigen/Dense>

// project
#include "ImageClasses/imageholder.h"
#include "ProgressLogger/progresslogger.h"

class DifferenceProcessor
{
public:
    enum DifferenceType { ABS = 0, POSITIVE = 1, NEGATIVE = 2 };

    DifferenceProcessor(int step = 1, DifferenceType diff_type = DifferenceType::ABS);
    void ProcessDifference(
            std::vector<std::shared_ptr<ImageHolder>> img_vect,
            std::vector<std::shared_ptr<ImageHolder>> *out_vect,
            std::string output_suffix,
            ProgressLogger *progress_logger = NULL);

private:
    int step;
    DifferenceType diff_type;

    std::shared_ptr<ImageHolder> ProcessImageDifference(
            std::shared_ptr<ImageHolder> img_in,
            std::shared_ptr<ImageHolder> back_img,
            std::string output_name);
};

#endif // DIFFERENCEPROCESSOR_H
