#ifndef IMAGEBUNDLE_H
#define IMAGEBUNDLE_H

#include <map>
#include <string>
#include <memory>
#include <QProgressBar>

#include "imageholder.h"

class ImageBundle
{
public:
    ImageBundle();

    void LoadImg(std::string img_name);
    void ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size);
    void ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size);
    void ProcessHistogramNormalization(std::string img_name, std::string output_name, QProgressBar *progress_bar = NULL);
    void ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma);
    void ProcessLogLawTransformation(std::string img_name, std::string output_name, double c);
    void ProcessThresholding(std::string img_name, std::string output_name, int threshold);
    void ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size);
    void ProcessErosion(std::string img_name, std::string output_name, int filter_size);
    void ProcessDilatation(std::string img_name, std::string output_name, int filter_size);
    void ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size);
    void ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size);
    void ProcessLMR(std::string img_name, std::string output_name, int filter_size);

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
