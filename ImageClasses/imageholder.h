#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include <memory>
#include <boost/filesystem.hpp>
#include <Eigen/Dense>
#include <QProgressBar>

#include "Segmentation/kmeans.h"

class ImageHolder
{
public:
    enum ImageType { GRAYSCALE, RGB, BGR };

    ImageHolder(std::string dir_path, std::string img_name);
    ImageHolder(Eigen::MatrixXi mat_img, std::string img_name, ImageType image_type);

    std::shared_ptr<ImageHolder> ProcessEdgeDetection(std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size);
    std::shared_ptr<ImageHolder> ProcessBothSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    std::shared_ptr<ImageHolder> ProcessVerticalSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    std::shared_ptr<ImageHolder> ProcessHorizontalSobel(std::string output_name, bool use_gaussian_blur, int gaussian_filter_size);
    std::shared_ptr<ImageHolder> ProcessGaussianBlur(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessHistogramNormalization(std::string output_name);
    std::shared_ptr<ImageHolder> ProcessPowerLawTransformation(std::string output_name, double gamma);
    std::shared_ptr<ImageHolder> ProcessLogLawTransformation(std::string output_name, double c);
    std::shared_ptr<ImageHolder> ProcessThresholding(std::string output_name, int threshold);
    std::shared_ptr<ImageHolder> ProcessMedianFilter(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessErosion(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessDilatation(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessErosionDilatation(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessUnsharpMask(std::string output_name, double alpha, bool save_mask, int filter_size);
    std::shared_ptr<ImageHolder> ProcessLMR(std::string output_name, int filter_size);
    std::shared_ptr<ImageHolder> ProcessCanny(std::string output_name, bool save_tmp_imgs);
    std::shared_ptr<ImageHolder> ProcessOtsuSegmentation(std::string output_name);
    std::shared_ptr<ImageHolder> ProcessKMeans(std::string output_name, int k, KMeans::K_MEANS_DISTANCE distance_method);
    std::shared_ptr<ImageHolder> ProcessNegative(std::string output_name);


    void SetImageName(std::string name);
    void SetImageType(ImageType type);

    std::string GetImageName();
    ImageType GetImageType();

    int GetRows() {return mat_img.rows();}
    int GetCols() {return mat_img.cols();}

    bool GetIsLoaded(){return is_loaded;}

    static bool Compare(const ImageHolder img1, const ImageHolder img2){
        return img1.img_name.compare(img2.img_name) < 0;
    }

    Eigen::MatrixXi mat_img;

private:
    std::string img_name;
    ImageType img_type;
    bool is_loaded;
};



#endif // IMAGEHOLDER_H
