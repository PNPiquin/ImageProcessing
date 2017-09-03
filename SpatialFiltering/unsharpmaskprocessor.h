#ifndef UNSHARPMASKPROCESSOR_H
#define UNSHARPMASKPROCESSOR_H

#include <Eigen/Dense>
#include "SpatialFiltering/CommonSpatialFilters.h"
#include "SpatialFiltering/IntensityTransformation.h"
#include "IO/JpegManager.h"

class UnsharpMaskProcessor
{
public:
    UnsharpMaskProcessor();

    static void ProcessUnsharpMask(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, double unsharp_coeff, bool save_unsharp_mask, int gaussian_filter_size = 5);
};

#endif // UNSHARPMASKPROCESSOR_H
