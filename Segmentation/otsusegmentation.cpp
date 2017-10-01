#include "otsusegmentation.h"
#include "SpatialFiltering/HistogramProcessor.h"
#include "SpatialFiltering/IntensityTransformation.h"

OtsuSegmentation::OtsuSegmentation()
{

}

void OtsuSegmentation::ProcessOtsuSegmentation(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out){
    int rows = img.rows();
    int cols = img.cols();
    img_out.resize(rows, cols);
    int L = 256;
    Eigen::MatrixXi img_normalized(rows, cols);

    HistogramProcessor hp;
    hp.ProcessEqualization(img, img_normalized);
    std::map<int, double> histogram = HistogramProcessor::GetHistogram(img_normalized);

    std::map<int, double> P1_k; // key = k, value = P1(k)
    std::map<int, double> mean_k;
    for(int k = 0; k < L; ++k){
        P1_k[k] = 0;
        mean_k[k] = 0;
        for(int l = 0; l <= k; ++l){
            P1_k[k] += histogram[l];
            mean_k[k] += l * histogram[l];
        }
    }

    double mean_global(mean_k[L-1]);
//    for(int i = 0; i < 256; ++i){
//        mean_global += i * histogram[i];
//    }

    std::map<int, double> between_class_variances;
    for(int k = 0; k < L; ++k){
        between_class_variances[k] = std::pow(mean_global * P1_k[k] - mean_k[k], 2) / (P1_k[k] * (1 - P1_k[k]));
    }

    double variance_max(0.0);
    int k_max(0);
    for(int k = 0; k < L; ++k){
        if(between_class_variances[k] > variance_max){
            variance_max = between_class_variances[k];
            k_max = k;
        }
    }

    IntensityTransformation::ProcessThresholding(img_normalized, img_out, k_max);
}
