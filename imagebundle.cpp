#include "imagebundle.h"

ImageBundle::ImageBundle()
{
    working_dir_path = "/home/pierre-nicolas/Pictures/ImageProcessing/";
}

void ImageBundle::LoadImg(std::string img_name){
    std::shared_ptr<ImageHolder> img_holder = std::make_shared<ImageHolder>(working_dir_path, img_name);
    image_bundle.insert(std::pair<std::string, std::shared_ptr<ImageHolder>>(img_name, img_holder));
    //JpegManager::SaveGrayscaleMatrixImg(img_holder->mat_img, working_dir_path + img_name + "_grayscale");
    image_bundle.insert(std::pair<std::string, std::shared_ptr<ImageHolder>>(img_name + "_grayscale", img_holder));
}

void ImageBundle::ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessEdgeDetection(output_name, filter_size, use_gaussian_blur, gaussian_filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(edge_img->mat_img, working_dir_path + output_name);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessGaussianBlur(output_name, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(edge_img->mat_img, working_dir_path + output_name);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessHistogramNormalization(std::string img_name, std::string output_name){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> histogram_img = img->ProcessHistogramNormalization(output_name);
    //JpegManager::SaveGrayscaleMatrixImg(histogram_img->mat_img, working_dir_path + output_name);
    Insert(output_name, histogram_img);
}

void ImageBundle::ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> pow_img = img->ProcessPowerLawTransformation(output_name, gamma);
    //JpegManager::SaveGrayscaleMatrixImg(pow_img->mat_img, working_dir_path + output_name);
    Insert(output_name, pow_img);
}

void ImageBundle::ProcessLogLawTransformation(std::string img_name, std::string output_name, double c){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> log_img = img->ProcessPowerLawTransformation(output_name, c);
    //JpegManager::SaveGrayscaleMatrixImg(log_img->mat_img, working_dir_path + output_name);
    Insert(output_name, log_img);
}

void ImageBundle::ProcessThresholding(std::string img_name, std::string output_name, int threshold){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> log_img = img->ProcessThresholding(output_name, threshold);
    //JpegManager::SaveGrayscaleMatrixImg(log_img->mat_img, working_dir_path + output_name);
    Insert(output_name, log_img);
}

void ImageBundle::ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> median_img = img->ProcessMedianFilter(output_name, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(median_img->mat_img, working_dir_path + output_name);
    Insert(output_name, median_img);
}

void ImageBundle::ProcessErosion(std::string img_name, std::string output_name, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> erosion_img = img->ProcessErosion(output_name, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(erosion_img->mat_img, working_dir_path + output_name);
    Insert(output_name, erosion_img);
}

void ImageBundle::ProcessDilatation(std::string img_name, std::string output_name, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> dilatation_img = img->ProcessGaussianBlur(output_name, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(dilatation_img->mat_img, working_dir_path + output_name);
    Insert(output_name, dilatation_img);
}

void ImageBundle::ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> erosion_dilatation_img = img->ProcessGaussianBlur(output_name, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(erosion_dilatation_img->mat_img, working_dir_path + output_name);
    Insert(output_name, erosion_dilatation_img);
}

void ImageBundle::ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size){
    std::shared_ptr<ImageHolder> img = image_bundle.at(img_name);
    std::shared_ptr<ImageHolder> sharp_img = img->ProcessUnsharpMask(output_name, alpha, save_mask, filter_size);
    //JpegManager::SaveGrayscaleMatrixImg(sharp_img->mat_img, working_dir_path + output_name);
    Insert(output_name, sharp_img);
}
