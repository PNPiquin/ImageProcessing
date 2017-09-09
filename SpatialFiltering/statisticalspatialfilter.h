#ifndef STATISTICALSPATIALFILTER_H
#define STATISTICALSPATIALFILTER_H

#include <vector>
#include <Eigen/Dense>
#include <QProgressBar>


class StatisticalSpatialFilter
{
public:
    StatisticalSpatialFilter();
    void SetFilterSize(int size);
    void SetStatisticalFilter(std::function<int(std::vector<int>)> func);
    void ProcessStatisticalFilter(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar=NULL);

private:
    int filter_size;
    std::function<int(std::vector<int>)> statistical_filter;

    void subMatrixExtraction(int i, int j, Eigen::MatrixXi &img, std::vector<int> &out_vector);
};

class MedianFilter : public StatisticalSpatialFilter {
public:
    MedianFilter(int filter_size);
};

class MaxFilter : public StatisticalSpatialFilter {
public:
    MaxFilter(int filter_size);
};

class MinFilter : public StatisticalSpatialFilter {
public:
    MinFilter(int filter_size);
};

class SlowLMRProcessor : public StatisticalSpatialFilter {
public:
    SlowLMRProcessor(int filter_size);
};

#endif // STATISTICALSPATIALFILTER_H
