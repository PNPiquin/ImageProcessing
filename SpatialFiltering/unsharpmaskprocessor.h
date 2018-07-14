#ifndef UNSHARPMASKPROCESSOR_H
#define UNSHARPMASKPROCESSOR_H

#include <Eigen/Dense>
#include <QProgressBar>

#include "SpatialFiltering/CommonSpatialFilters.h"
#include "SpatialFiltering/IntensityTransformation.h"
#include "IO/JpegManager.h"
#include "ProgressLogger/progresslogger.h"

class UnsharpMaskProcessor
{
public:
    UnsharpMaskProcessor();

    static void ProcessUnsharpMask(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, double unsharp_coeff, bool save_unsharp_mask, int gaussian_filter_size = 5, ProgressLogger *progress_logger=NULL);
};

#endif // UNSHARPMASKPROCESSOR_H
