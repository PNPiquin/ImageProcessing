#ifndef OTSUSEGMENTATION_H
#define OTSUSEGMENTATION_H

#include <map>
#include <Eigen/Dense>

class OtsuSegmentation
{
public:
    OtsuSegmentation();

    static void ProcessOtsuSegmentation(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out);
};

#endif // OTSUSEGMENTATION_H
