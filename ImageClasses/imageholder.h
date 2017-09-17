#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <Eigen/Dense>
#include <QProgressBar>

#include "IO/JpegManager.h"
#include "SpatialFiltering/SpatialFilter.h"
#include "SpatialFiltering/CommonSpatialFilters.h"
#include "SpatialFiltering/HistogramProcessor.h"
#include "SpatialFiltering/IntensityTransformation.h"
#include "SpatialFiltering/statisticalspatialfilter.h"
#include "SpatialFiltering/unsharpmaskprocessor.h"
#include "SpatialFiltering/cannyedgedetector.h"

class ImageHolder
{
public:
    enum ImageType { GRAYSCALE, RGB, BGR };

    ImageHolder(std::string dir_path, std::string img_name);
    ImageHolder(Eigen::MatrixXi mat_img, std::string img_name, ImageType image_type);

    std::shared_ptr<ImageHolder> ProcessEdgeDetection(std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessBothSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessVerticalSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessHorizontalSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessGaussianBlur(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessHistogramNormalization(std::string output_name,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessPowerLawTransformation(std::string output_name, double gamma,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessLogLawTransformation(std::string output_name, double c,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessThresholding(std::string output_name, int threshold,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessMedianFilter(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessErosion(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessDilatation(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessErosionDilatation(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessUnsharpMask(std::string output_name, double alpha, bool save_mask, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessLMR(std::string output_name, int filter_size,  QProgressBar *progress_bar = NULL);
    std::shared_ptr<ImageHolder> ProcessCanny(std::string output_name, bool save_tmp_imgs,  QProgressBar *progress_bar = NULL);


    void SetImageName(std::string name);
    void SetImageType(ImageType type);

    std::string GetImageName();
    ImageType GetImageType();

    int GetRows() {return mat_img.rows();}
    int GetCols() {return mat_img.cols();}

    static bool Compare(const ImageHolder img1, const ImageHolder img2){
        return img1.img_name.compare(img2.img_name) < 0;
    }

    Eigen::MatrixXi mat_img;

private:
    std::string img_name;
    ImageType img_type;
};



#endif // IMAGEHOLDER_H
