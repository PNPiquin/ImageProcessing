#include "imageholder.h"

ImageHolder::ImageHolder(std::string dir_path, std::string img_name) :
    img_name(img_name)
{
    mat_img = Eigen::MatrixXi();
    JpegManager jpeg_manager(dir_path + img_name);
    jpeg_manager.GetGrayscaleMatrixImg(mat_img);
    img_type = ImageType::GRAYSCALE;
}

ImageHolder::ImageHolder(Eigen::MatrixXi mat_img, std::string img_name, ImageType image_type) :
    mat_img(mat_img),
    img_name(img_name),
    img_type(image_type)
{

}

void ImageHolder::SetImageName(std::string name){
    img_name = name;
}

void ImageHolder::SetImageType(ImageType type){
    img_type = type;
}

std::string ImageHolder::GetImageName(){
    return img_name;
}

ImageHolder::ImageType ImageHolder::GetImageType(){
    return img_type;
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessEdgeDetection(std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size){
    Eigen::MatrixXi img_out;

    if(use_gaussian_blur){
        Eigen::MatrixXi gaussian_img;
        GaussianBlurFilter gaussian_filter(gaussian_filter_size);
        EdgeDetectionFilter edge_filter(filter_size);
        gaussian_filter.ProcessMatrixImg(mat_img, gaussian_img);
        edge_filter.ProcessMatrixImg(gaussian_img, img_out);
    } else{
        EdgeDetectionFilter edge_filter(filter_size);
        edge_filter.ProcessMatrixImg(mat_img, img_out);
    }

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessGaussianBlur(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out;

    GaussianBlurFilter blur_filter(filter_size);
    blur_filter.ProcessMatrixImg(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessHistogramNormalization(std::string output_name){
    Eigen::MatrixXi img_out;

    HistogramProcessor hp;
    hp.ProcessEqualization(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessPowerLawTransformation(std::string output_name, double gamma){
    Eigen::MatrixXi img_out;

    IntensityTransformation::ProcessPowerLaw(mat_img, img_out, gamma);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessLogLawTransformation(std::string output_name, double c){
    Eigen::MatrixXi img_out;

    IntensityTransformation::ProcessLogLaw(mat_img, img_out, c);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessThresholding(std::string output_name, int threshold){
    Eigen::MatrixXi img_out;

    IntensityTransformation::ProcessThresholding(mat_img, img_out, threshold);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessMedianFilter(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out;

    MedianFilter median_filter(filter_size);
    median_filter.ProcessStatisticalFilter(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessDilatation(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out;

    MinFilter min_filter(filter_size);
    min_filter.ProcessStatisticalFilter(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessErosion(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out;

    MaxFilter max_filter(filter_size);
    max_filter.ProcessStatisticalFilter(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessErosionDilatation(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out, img_tmp;

    MaxFilter max_filter(filter_size);
    max_filter.ProcessStatisticalFilter(mat_img, img_tmp);

    MinFilter min_filter(filter_size);
    min_filter.ProcessStatisticalFilter(img_tmp, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessUnsharpMask(std::string output_name, double alpha, bool save_mask, int filter_size){
    Eigen::MatrixXi img_out;

    UnsharpMaskProcessor::ProcessUnsharpMask(mat_img, img_out, alpha, save_mask, filter_size);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}

std::shared_ptr<ImageHolder> ImageHolder::ProcessLMR(std::string output_name, int filter_size){
    Eigen::MatrixXi img_out;

    SlowLMRProcessor lmrp(filter_size);
    lmrp.ProcessStatisticalFilter(mat_img, img_out);

    return std::make_shared<ImageHolder>(img_out, output_name, ImageType::GRAYSCALE);
}
