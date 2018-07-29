#ifndef IMAGEBUNDLE_H
#define IMAGEBUNDLE_H

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <QProgressBar>
#include <boost/filesystem.hpp>

#include "imageholder.h"
#include "Segmentation/kmeans.h"

#include "ProgressLogger/progresslogger.h"

class ImageBundle
{
public:
    ImageBundle();

    // Utils
    void LoadImg(std::string img_name);
    void LoadImgFolder(std::string folder_name);
    std::shared_ptr<ImageHolder> FindImage(std::string img_name);
    void SaveImgGroup(std::string group_name, std::string save_folder);

    // Image processing pipelines
    void ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size);
    void ProcessBothSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    void ProcessVerticalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    void ProcessHorizontalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    void ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size);
    void ProcessHistogramNormalization(std::string img_name, std::string output_name);
    void ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma);
    void ProcessLogLawTransformation(std::string img_name, std::string output_name, double c);
    void ProcessThresholding(std::string img_name, std::string output_name, int threshold);
    void ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size);
    void ProcessErosion(std::string img_name, std::string output_name, int filter_size);
    void ProcessDilatation(std::string img_name, std::string output_name, int filter_size);
    void ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size);
    void ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size);
    void ProcessLMR(std::string img_name, std::string output_name, int filter_size);
    void ProcessCanny(std::string img_name, std::string output_name, bool save_tmp_imgs);
    void ProcessOtsuSegmentation(std::string img_name, std::string output_name);
    void ProcessKMeans(std::string img_name, std::string output_name, int k, KMeans::K_MEANS_DISTANCE distance_method);
    void ProcessNegative(std::string img_name, std::string output_name);
    void ProcessImageResize(std::string img_name, std::string output_name, int x0, int y0, int x1, int y1);

    void SetWorkingDir(std::string path) {working_dir_path = path; }
    std::string GetWorkingDir() {return working_dir_path;}

    void DeleteImageGroup(std::string name);

    std::vector<std::shared_ptr<ImageHolder>> FindImageVector(std::string img_name);

    std::map<std::string, std::vector<std::shared_ptr<ImageHolder>>> image_bundle;

    int GetProgress();

private:
    // Utils
    void Insert(std::string img_name, std::shared_ptr<ImageHolder> img);
    void Insert(std::string img_name, std::vector<std::shared_ptr<ImageHolder>>);

    std::string working_dir_path;
    ProgressLogger *progress_logger;
};

#endif // IMAGEBUNDLE_H
