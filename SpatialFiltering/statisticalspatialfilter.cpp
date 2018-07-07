#include "statisticalspatialfilter.h"

StatisticalSpatialFilter::StatisticalSpatialFilter()
{

}

void StatisticalSpatialFilter::SetFilterSize(int size){
    filter_size = size;
}

void StatisticalSpatialFilter::SetStatisticalFilter(std::function<int(std::vector<int>)> func){
    statistical_filter = func;
}

void StatisticalSpatialFilter::ProcessStatisticalFilter(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar){
    int rows = img.rows();
    int cols = img.cols();
    int padding = (filter_size - 1) / 2;
    img_out.resize(rows, cols);
    // printf("%s\n", "Starting StatisticalSpatialFilter processing");
    for(int i = padding; i < rows - padding; ++i){
        for(int j = padding; j < cols - padding; ++j){
            std::vector<int> tmp_data;
            subMatrixExtraction(i, j, img, tmp_data);
            img_out(i, j) = statistical_filter(tmp_data);
        }
        if(progress_bar){
            progress_bar->setValue(std::floor(((i+1)*100)/(rows-padding)));
        }
    }
    // printf("%s\n", "End of StatisticalSpatialFilter processing");
}

void StatisticalSpatialFilter::subMatrixExtraction(int i, int j, Eigen::MatrixXi &img, std::vector<int> &out_vector){
    out_vector.clear();
    int padding = (filter_size - 1) / 2;
    for(int l = i - padding; l <= i + padding; ++l){
        for(int k = j - padding; k <= j + padding; ++k){
            out_vector.push_back(img(l, k));
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                      Median Filter
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

MedianFilter::MedianFilter(int filter_size) : StatisticalSpatialFilter() {
    SetFilterSize(filter_size);
    auto median_filter = [](std::vector<int> data){
        std::sort(data.begin(), data.end());
        int n = data.size();
        return data[(int) ((n+1)/2)];
    };
    SetStatisticalFilter(median_filter);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                      Max Filter
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

MaxFilter::MaxFilter(int filter_size) : StatisticalSpatialFilter() {
    SetFilterSize(filter_size);
    auto max_filter = [](std::vector<int> data){
        std::sort(data.begin(), data.end());
        return data.back();
    };
    SetStatisticalFilter(max_filter);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                       Min Filter
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

MinFilter::MinFilter(int filter_size) : StatisticalSpatialFilter() {
    SetFilterSize(filter_size);
    auto min_filter = [](std::vector<int> data){
        std::sort(data.begin(), data.end());
        return data.front();
    };
    SetStatisticalFilter(min_filter);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                       Slow and stupid method to do a Local Mean Removal
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

SlowLMRProcessor::SlowLMRProcessor(int filter_size) : StatisticalSpatialFilter() {
    SetFilterSize(filter_size);
    auto min_filter = [](std::vector<int> data){
        int lmr_value(0);
        for(auto value : data){
            lmr_value += value;
        }
        lmr_value /= data.size();
        return lmr_value;
    };
    SetStatisticalFilter(min_filter);
}
