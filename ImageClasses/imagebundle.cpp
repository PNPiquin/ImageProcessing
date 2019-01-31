#include "imagebundle.h"
#include "IO/ImageIOManager.h"

ImageBundle::ImageBundle()
{
#ifdef __MINGW32__
    working_dir_path = "D:\\Images\\ImageProcessing\\";
#else
    working_dir_path = "/home/pierre-nicolas/Pictures/ImageProcessing/";
#endif

    progress_logger = new ProgressLogger();
}

// -----------------------------------------------------------------------------------
//                                      Utils
// -----------------------------------------------------------------------------------
void ImageBundle::LoadImg(std::string img_name){
    std::shared_ptr<ImageHolder> img_holder = std::make_shared<ImageHolder>(working_dir_path, img_name);
    if(img_holder->GetIsLoaded()){
      Insert(img_name + "_grayscale", img_holder);
    }
}
void ImageBundle::LoadImgFolder(std::string folder_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vect;

    // path creation
    boost::filesystem::path working_dir(working_dir_path), folder(folder_name);
    boost::filesystem::path folder_path = working_dir / folder;

    if(boost::filesystem::is_directory(folder_path.string())){
        std::vector<boost::filesystem::path> paths;

        for (auto & p : boost::filesystem::directory_iterator(folder_path.string())){
            paths.push_back(p);
        }

        std::sort(paths.begin(), paths.end());

        for(int path_index = 0; path_index < int(paths.size()); ++path_index){
            boost::filesystem::path p = paths[unsigned(path_index)];
            std::shared_ptr<ImageHolder> img_holder = std::make_shared<ImageHolder>(p.parent_path().string() + "/", p.stem().string());
            img_vect.push_back(img_holder);
        }
        Insert(folder_name, img_vect);
    }
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

void ImageBundle::SaveImgGroup(std::string group_name, std::string save_folder){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(group_name);
    boost::filesystem::create_directory(boost::filesystem::path(working_dir_path + group_name));
    for(auto img : img_vector){
        std::cout << img->GetImageName() << std::endl;
        ImageIOManager::SaveGrayscaleMatrixImg(img->mat_img, working_dir_path + save_folder + "/" + img->GetImageName());
    }
}

int ImageBundle::GetProgress(){
    return progress_logger->GetProgress();
}

void ImageBundle::DeleteImageGroup(std::string name){
    image_bundle.erase(name);
}

// -----------------------------------------------------------------------------------
//                            Image processing
// -----------------------------------------------------------------------------------
void ImageBundle::ProcessEdgeDetection(
        std::string img_name,
        std::string output_name,
        int filter_size,
        bool use_gaussian_blur,
        int gaussian_filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    // The number of tasks to be done per image depends on if we use a gaussian
    // filter first or not
    const int tasks_per_img = use_gaussian_blur ? 2 : 1;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(tasks_per_img * int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessEdgeDetection(
                    img->GetImageName() + output_name,
                    filter_size,
                    use_gaussian_blur,
                    gaussian_filter_size,
                    progress_logger);
        out_img_vector.push_back(edge_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessBothSobel(
        std::string img_name,
        std::string output_name,
        bool use_gaussian_blur,
        int gaussian_filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    // The number of tasks to be done per image depends on if we use a gaussian
    // filter first or not
    const int tasks_per_img = use_gaussian_blur ? 3 : 2;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(tasks_per_img * int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessBothSobel(
                    img->GetImageName() + output_name,
                    use_gaussian_blur,
                    gaussian_filter_size,
                    progress_logger);
        out_img_vector.push_back(edge_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessVerticalSobel(
        std::string img_name,
        std::string output_name,
        bool use_gaussian_blur,
        int gaussian_filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    // The number of tasks to be done per image depends on if we use a gaussian
    // filter first or not
    const int tasks_per_img = use_gaussian_blur ? 2 : 1;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(tasks_per_img * int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessVerticalSobel(
                    img->GetImageName() + output_name,
                    use_gaussian_blur,
                    gaussian_filter_size,
                    progress_logger);
        out_img_vector.push_back(edge_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessHorizontalSobel(std::string img_name, std::string output_name, bool use_gaussian_blur, int gaussian_filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    // The number of tasks to be done per image depends on if we use a gaussian
    // filter first or not
    const int tasks_per_img = use_gaussian_blur ? 2 : 1;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(tasks_per_img * int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessHorizontalSobel(
                    img->GetImageName() + output_name,
                    use_gaussian_blur,
                    gaussian_filter_size,
                    progress_logger);
        out_img_vector.push_back(edge_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessGaussianBlur(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> edge_img = img->ProcessGaussianBlur(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(edge_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessHistogramNormalization(std::string img_name, std::string output_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> histogram_img = img->ProcessHistogramNormalization(
                    img->GetImageName() + output_name,
                    progress_logger);
        out_img_vector.push_back(histogram_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessPowerLawTransformation(std::string img_name, std::string output_name, double gamma){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> pow_img = img->ProcessPowerLawTransformation(
                    img->GetImageName() + output_name,
                    gamma,
                    progress_logger);
        out_img_vector.push_back(pow_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessLogLawTransformation(std::string img_name, std::string output_name, double c){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> log_img = img->ProcessPowerLawTransformation(
                    img->GetImageName() + output_name,
                    c,
                    progress_logger);
        out_img_vector.push_back(log_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessThresholding(std::string img_name, std::string output_name, int threshold){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> log_img = img->ProcessThresholding(
                    img->GetImageName() + output_name,
                    threshold,
                    progress_logger);
        out_img_vector.push_back(log_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessMedianFilter(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> median_img = img->ProcessMedianFilter(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(median_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessErosion(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> erosion_img = img->ProcessErosion(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(erosion_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessDilatation(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> dilatation_img = img->ProcessDilatation(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(dilatation_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessErosionDilatation(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> erosion_dilatation_img = img->ProcessErosionDilatation(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(erosion_dilatation_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessUnsharpMask(
        std::string img_name,
        std::string output_name,
        double alpha,
        bool save_mask,
        int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> sharp_img = img->ProcessUnsharpMask(
                    img->GetImageName() + output_name,
                    alpha,
                    save_mask,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(sharp_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessLMR(std::string img_name, std::string output_name, int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> sharp_img = img->ProcessLMR(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(sharp_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessCanny(std::string img_name, std::string output_name, bool save_tmp_imgs){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    const int tasks_per_img = 4;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(tasks_per_img * int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> canny_img = img->ProcessCanny(
                    img->GetImageName() + output_name,
                    save_tmp_imgs,
                    progress_logger);
        out_img_vector.push_back(canny_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
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

void ImageBundle::ProcessNegative(std::string img_name, std::string output_name){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> neg_img = img->ProcessNegative(
                    img->GetImageName() + output_name,
                    progress_logger);
        out_img_vector.push_back(neg_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessImageResize(std::string img_name, std::string output_name, int x0, int y0, int x1, int y1){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> resized_img = img->ProcessImageResize(
                    img->GetImageName() + output_name,
                    x0, y0, x1, y1,
                    progress_logger);
        out_img_vector.push_back(resized_img);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessDifference(
        std::string img_name,
        std::string output_suffix,
        int step,
        DifferenceProcessor::DifferenceType diff_type){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_vect;

    progress_logger->ResetProgressLogger();

    DifferenceProcessor dp(step, diff_type);
    dp.ProcessDifference(img_vector, &out_vect, output_suffix, progress_logger);

    Insert(img_name + output_suffix, out_vect);
}

void ImageBundle::ProcessMorphVGradient(
        std::string img_name,
        std::string output_name,
        int size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> img_out = img->ProcessMorphVGradient(
                    img->GetImageName() + output_name,
                    size,
                    progress_logger);
        out_img_vector.push_back(img_out);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessMorphHGradient(
        std::string img_name,
        std::string output_name,
        int size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> img_out = img->ProcessMorphHGradient(
                    img->GetImageName() + output_name,
                    size,
                    progress_logger);
        out_img_vector.push_back(img_out);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}

void ImageBundle::ProcessMorphEdgeDetection(
        std::string img_name,
        std::string output_name,
        int filter_size){
    std::vector<std::shared_ptr<ImageHolder>> img_vector = FindImageVector(img_name);
    std::vector<std::shared_ptr<ImageHolder>> out_img_vector;

    progress_logger->ResetProgressLogger();
    progress_logger->SetIsProcessing(true);
    progress_logger->SetTaskNumber(int(img_vector.size()));
    for(auto img : img_vector){
        std::shared_ptr<ImageHolder> img_out = img->ProcessMorphEdgeDetection(
                    img->GetImageName() + output_name,
                    filter_size,
                    progress_logger);
        out_img_vector.push_back(img_out);

        progress_logger->IncrementFinishedTasksCpt();
    }
    Insert(output_name, out_img_vector);

    progress_logger->SetIsProcessing(false);
}
