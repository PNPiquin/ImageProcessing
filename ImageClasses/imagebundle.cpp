#include "imagebundle.h"

ImageBundle::ImageBundle()
{
    working_dir_path = "/home/pierre-nicolas/Pictures/ImageProcessing/";
}

// -----------------------------------------------------------------------------------
//                                      Utils
// -----------------------------------------------------------------------------------
void ImageBundle::LoadImg(std::string img_name){
    std::shared_ptr<ImageHolder> img_holder = std::make_shared<ImageHolder>(working_dir_path, img_name);
    Insert(img_name + "_grayscale", img_holder);
}

void ImageBundle::Insert(std::string img_name, std::shared_ptr<ImageHolder> img){
    std::vector<std::shared_ptr<ImageHolder>> img_vector;
    img_vector.push_back(img);
    image_bundle.insert(std::pair<std::string,  std::vector<std::shared_ptr<ImageHolder>>>(img_name, img_vector));
}

std::shared_ptr<ImageHolder> ImageBundle::find_image(std::string img_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = image_bundle.at(img_name);
    return img_vector.front();
}

std::vector<std::shared_ptr<ImageHolder>> ImageBundle::find_image_vector(std::string img_name){
    return image_bundle.at(img_name);
}

// -----------------------------------------------------------------------------------
//                            Image processing
// -----------------------------------------------------------------------------------
void ImageBundle::ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessEdgeDetection(output_name, filter_size, use_gaussian_blur, gaussian_filter_size, progress_bar);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessBothSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessBothSobel(output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessVerticalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessVerticalSobel(output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessHorizontalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessHorizontalSobel(output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> edge_img = img->ProcessGaussianBlur(output_name, filter_size, progress_bar);
    Insert(output_name, edge_img);
}

void ImageBundle::ProcessHistogramNormalization(std::string img_name, std::string output_name, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> histogram_img = img->ProcessHistogramNormalization(output_name, progress_bar);
    Insert(output_name, histogram_img);
}

void ImageBundle::ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> pow_img = img->ProcessPowerLawTransformation(output_name, gamma, progress_bar);
    Insert(output_name, pow_img);
}

void ImageBundle::ProcessLogLawTransformation(std::string img_name, std::string output_name, double c, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> log_img = img->ProcessPowerLawTransformation(output_name, c, progress_bar);
    Insert(output_name, log_img);
}

void ImageBundle::ProcessThresholding(std::string img_name, std::string output_name, int threshold, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> log_img = img->ProcessThresholding(output_name, threshold, progress_bar);
    Insert(output_name, log_img);
}

void ImageBundle::ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> median_img = img->ProcessMedianFilter(output_name, filter_size, progress_bar);
    Insert(output_name, median_img);
}

void ImageBundle::ProcessErosion(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> erosion_img = img->ProcessErosion(output_name, filter_size, progress_bar);
    Insert(output_name, erosion_img);
}

void ImageBundle::ProcessDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> dilatation_img = img->ProcessDilatation(output_name, filter_size, progress_bar);
    Insert(output_name, dilatation_img);
}

void ImageBundle::ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> erosion_dilatation_img = img->ProcessErosionDilatation(output_name, filter_size, progress_bar);
    Insert(output_name, erosion_dilatation_img);
}

void ImageBundle::ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> sharp_img = img->ProcessUnsharpMask(output_name, alpha, save_mask, filter_size, progress_bar);
    Insert(output_name, sharp_img);
}

void ImageBundle::ProcessLMR(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> sharp_img = img->ProcessLMR(output_name, filter_size, progress_bar);
    Insert(output_name, sharp_img);
}

void ImageBundle::ProcessCanny(std::string img_name, std::string output_name, bool save_tmp_imgs, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> canny_img = img->ProcessCanny(output_name, save_tmp_imgs, progress_bar);
    Insert(output_name, canny_img);
}

void ImageBundle::ProcessOtsuSegmentation(std::string img_name, std::string output_name){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> otsu_img = img->ProcessOtsuSegmentation(output_name);
    Insert(output_name, otsu_img);
}

void ImageBundle::ProcessKMeans(std::string img_name, std::string output_name, int k, KMeans::K_MEANS_DISTANCE distance_method){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> k_img = img->ProcessKMeans(output_name, k, distance_method);
    Insert(output_name, k_img);
}

void ImageBundle::ProcessNegative(std::string img_name, std::string output_name, QProgressBar *progress_bar){
    std::shared_ptr<ImageHolder> img = find_image(img_name);
    std::shared_ptr<ImageHolder> neg_img = img->ProcessNegative(output_name, progress_bar);
    Insert(output_name, neg_img);
}
