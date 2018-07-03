#ifndef IMAGEBUNDLE_H
#define IMAGEBUNDLE_H

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <QProgressBar>
#include <boost/filesystem.hpp>

#include "imageholder.h"
#include "Segmentation/kmeans.h"

class ImageBundle
{
public:
    ImageBundle();

    // Utils
    void LoadImg(std::string img_name);
    void LoadImgFolder(std::string folder_name);
    std::shared_ptr<ImageHolder> FindImage(std::string img_name);
    void SaveImgGroup(std::string group_name);

    // Image processing pipelines
    void ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar = NULL);
    void ProcessBothSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar = NULL);
    void ProcessVerticalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar = NULL);
    void ProcessHorizontalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar = NULL);
    void ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessHistogramNormalization(std::string img_name, std::string output_name, QProgressBar *progress_bar = NULL);
    void ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma, QProgressBar *progress_bar = NULL);
    void ProcessLogLawTransformation(std::string img_name, std::string output_name, double c, QProgressBar *progress_bar = NULL);
    void ProcessThresholding(std::string img_name, std::string output_name, int threshold, QProgressBar *progress_bar = NULL);
    void ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessErosion(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessLMR(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar = NULL);
    void ProcessCanny(std::string img_name, std::string output_name, bool save_tmp_imgs, QProgressBar *progress_bar = NULL);
    void ProcessOtsuSegmentation(std::string img_name, std::string output_name);
    void ProcessKMeans(std::string img_name, std::string output_name, int k, KMeans::K_MEANS_DISTANCE distance_method);
    void ProcessNegative(std::string img_name, std::string output_name, QProgressBar *progress_bar = NULL);

    void SetWorkingDir(std::string path) {working_dir_path = path; }
    std::string GetWorkingDir() {return working_dir_path;}

    std::map<std::string, std::vector<std::shared_ptr<ImageHolder>>> image_bundle;

private:
    // Utils
    void Insert(std::string img_name, std::shared_ptr<ImageHolder> img);
    void Insert(std::string img_name, std::vector<std::shared_ptr<ImageHolder>>);
    std::vector<std::shared_ptr<ImageHolder>> FindImageVector(std::string img_name);

    std::string working_dir_path;
};

#endif // IMAGEBUNDLE_H
