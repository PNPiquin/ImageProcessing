#include "imagebundle.h"
#include "IO/JpegManager.h"

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
void ImageBundle::LoadImgFolder(std::string folder_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vect;
    for (auto & p : boost::filesystem::directory_iterator(working_dir_path + folder_name)){
        std::shared_ptr<ImageHolder> img_holder = std::make_shared<ImageHolder>(p.path().parent_path().string() + "/", p.path().stem().string());
        img_vect.push_back(img_holder);
    }
    Insert(folder_name, img_vect);
}

void ImageBundle::Insert(std::string img_name, std::shared_ptr<ImageHolder> img){
    std::vector<std::shared_ptr<ImageHolder>> img_vector;
    img_vector.push_back(img);
    image_bundle.insert(std::pair<std::string,  std::vector<std::shared_ptr<ImageHolder>>>(img_name, img_vector));
}

void ImageBundle::Insert(std::string img_name, std::vector<std::shared_ptr<ImageHolder>> img_vect){
    image_bundle.insert(std::pair<std::string,  std::vector<std::shared_ptr<ImageHolder>>>(img_name, img_vect));
}

std::shared_ptr<ImageHolder> ImageBundle::FindImage(std::string img_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = image_bundle.at(img_name);
    return img_vector.front();
}

std::vector<std::shared_ptr<ImageHolder>> ImageBundle::FindImageVector(std::string img_name){
    return image_bundle.at(img_name);
}

void ImageBundle::SaveImgGroup(std::string group_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(group_name);
    boost::filesystem::create_directory(boost::filesystem::path(working_dir_path + group_name));
    for(auto img : img_vector){
        JpegManager::SaveGrayscaleMatrixImg(img->mat_img, working_dir_path + group_name + "/" + img->GetImageName());
    }
}

// -----------------------------------------------------------------------------------
//                            Image processing
// -----------------------------------------------------------------------------------
void ImageBundle::ProcessEdgeDetection(std::string img_name, std::string output_name, int filter_size, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessEdgeDetection(img->GetImageName() + output_name,
                                                                          filter_size, use_gaussian_blur, gaussian_filter_size, progress_bar);
        out_img_vector.push_back(edge_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessBothSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessBothSobel(img->GetImageName() + output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
        out_img_vector.push_back(edge_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessVerticalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessVerticalSobel(img->GetImageName() + output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
        out_img_vector.push_back(edge_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessHorizontalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessHorizontalSobel(img->GetImageName() + output_name, use_gaussian_blur, gaussian_filter_size, progress_bar);
        out_img_vector.push_back(edge_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessGaussianBlur(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(edge_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessHistogramNormalization(std::string img_name, std::string output_name, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> histogram_img = img->ProcessHistogramNormalization(img->GetImageName() + output_name, progress_bar);
        out_img_vector.push_back(histogram_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> pow_img = img->ProcessPowerLawTransformation(img->GetImageName() + output_name, gamma, progress_bar);
        out_img_vector.push_back(pow_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessLogLawTransformation(std::string img_name, std::string output_name, double c, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> log_img = img->ProcessPowerLawTransformation(img->GetImageName() + output_name, c, progress_bar);
        out_img_vector.push_back(log_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessThresholding(std::string img_name, std::string output_name, int threshold, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> log_img = img->ProcessThresholding(img->GetImageName() + output_name, threshold, progress_bar);
        out_img_vector.push_back(log_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> median_img = img->ProcessMedianFilter(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(median_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessErosion(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> erosion_img = img->ProcessErosion(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(erosion_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> dilatation_img = img->ProcessDilatation(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(dilatation_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> erosion_dilatation_img = img->ProcessErosionDilatation(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(erosion_dilatation_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessUnsharpMask(std::string img_name, std::string output_name, double alpha, bool save_mask, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> sharp_img = img->ProcessUnsharpMask(img->GetImageName() + output_name, alpha, save_mask, filter_size, progress_bar);
        out_img_vector.push_back(sharp_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessLMR(std::string img_name, std::string output_name, int filter_size, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> sharp_img = img->ProcessLMR(img->GetImageName() + output_name, filter_size, progress_bar);
        out_img_vector.push_back(sharp_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessCanny(std::string img_name, std::string output_name, bool save_tmp_imgs, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> canny_img = img->ProcessCanny(img->GetImageName() + output_name, save_tmp_imgs, progress_bar);
        out_img_vector.push_back(canny_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessOtsuSegmentation(std::string img_name, std::string output_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> otsu_img = img->ProcessOtsuSegmentation(output_name);
        out_img_vector.push_back(otsu_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessKMeans(std::string img_name, std::string output_name, int k, KMeans::K_MEANS_DISTANCE distance_method){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> k_img = img->ProcessKMeans(img->GetImageName() + output_name, k, distance_method);
        out_img_vector.push_back(k_img);
    }
    Insert(output_name, out_img_vector);
}

void ImageBundle::ProcessNegative(std::string img_name, std::string output_name, QProgressBar *progress_bar){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> neg_img = img->ProcessNegative(img->GetImageName() + output_name, progress_bar);
        out_img_vector.push_back(neg_img);
    }
    Insert(output_name, out_img_vector);
}
