#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <set>
#include <map>
#include <functional>
#include <Eigen/Dense>

class KMeans
{
public:

    enum K_MEANS_DISTANCE {
        EUCLIDIAN_DISTANCE,
        ED_SVD, // Euclidian distance + square value diff
        SVD // square value diff
    };

    KMeans(int k = 2, K_MEANS_DISTANCE distance_method = ED_SVD);
    void ProcessKMeans(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out);

    struct Pixel{
        int x;
        int y;
        int value;
        Pixel(){
            x = 0;
            y = 0;
            value = 0;
        }

        Pixel(int i, int j, int v){
            x = i;
            y = j;
            value = v;
        }

        void SetCoord(int xx, int yy){
            x = xx;
            y = yy;
        }
        void UpdateValue(Eigen::MatrixXi &img){
            value = img(x, y);
        }
    };

private:
    int number_of_clusters;

    struct Cluster{
        double total_dist;
        Pixel cluster_center;
        std::vector<Pixel> pixels;
        Cluster(){
            total_dist = 0;
        }
        void ClearPixels(){
            pixels.clear();
        }
    };

    std::map<int, Cluster> clusters;
    std::function<double(Pixel, Pixel)> distance;

    void Init(Eigen::MatrixXi &img, int x_min, int x_max, int y_min, int y_max); // Create k seeds in the area delimited by x_min, x_max, y_min, y_max
    double ProcessKMeansStep(Eigen::MatrixXi &img);
    int FindClosestCluster(Pixel p, double &dist);
};

#endif // KMEANS_H
