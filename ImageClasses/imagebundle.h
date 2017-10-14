#ifndef IMAGEBUNDLE_H
#define IMAGEBUNDLE_H

#include <map>
#include <string>
#include <memory>
#include <QProgressBar>

#include "imageholder.h"
#include "Segmentation/kmeans.h"

class ImageBundle
{
public:
    ImageBundle();

    void LoadImg(std::string img_name);
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


    void SetWorkingDir(std::string path) {working_dir_path = path; }
    std::string GetWorkingDir() {return working_dir_path;}

    void Insert(std::string img_name, std::shared_ptr<ImageHolder> img){
        image_bundle.insert(std::pair<std::string, std::shared_ptr<ImageHolder>>(img_name, img));
    }

    std::map<std::string, std::shared_ptr<ImageHolder>> image_bundle;

private:
    std::string working_dir_path;
};

#endif // IMAGEBUNDLE_H
