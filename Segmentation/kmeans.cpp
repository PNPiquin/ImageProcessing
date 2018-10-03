#include "kmeans.h"
#include <random>

KMeans::KMeans(int k, K_MEANS_DISTANCE distance_method) :
    number_of_clusters(k)
{
    for(int i = 0; i < number_of_clusters; ++i){
        clusters.insert(std::pair<int, Cluster>(i, Cluster()));
    }
    switch(distance_method){
    case ED_SVD:
        distance = [](Pixel p1, Pixel p2){
            double euclidian_distance = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
            double value_dist = (std::pow(p1.value - p2.value, 2));
            return (euclidian_distance + value_dist) / 2;
        };
        break;
    case EUCLIDIAN_DISTANCE:
        distance = [](Pixel p1, Pixel p2){
            return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
        };
        break;
    case SVD:
        distance = [](Pixel p1, Pixel p2){
            return std::sqrt(std::pow(p1.value - p2.value, 2));
        };
        break;
    }
}

void KMeans::ProcessKMeans(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out){
    int rows = img.rows();
    int cols = img.cols();
    img_out.resize(rows, cols);

    // Initialization of cluster centers
    Init(img, 0, rows - 1, 0, cols - 1);

    int max_iter(25), iter(0);
    double epsilon(1.0), prev_value(0.0);
    double total_value = - epsilon - 1.0;
    while(std::abs(total_value - prev_value) > epsilon && iter < max_iter){
        prev_value = total_value;
        ++iter;
        total_value = ProcessKMeansStep(img);
        total_value /= (rows * cols);
    }

    // printf("iter : %d || delta : %f \n", iter, std::abs(total_value - prev_value));

    int color_inc = int(255 / (number_of_clusters - 1));
    for(int index = 0; index < number_of_clusters; ++index){
        int color = index * color_inc;
        for(const auto &px : clusters.at(index).pixels){
            img_out(px.x, px.y) = color;
        }
    }

    /*
    std::vector<Cluster*> cluster_vect;
    for(int i = 0; i < number_of_clusters; ++i){
        cluster_vect.push_back(&clusters.at(i));
    }
    std::sort(cluster_vect.begin(), cluster_vect.end(), [](Cluster *c1, Cluster *c2){
        return c1->cluster_center.value < c2->cluster_center.value;
    });

    int color_inc = (int)(255 / (number_of_clusters - 1));
    for(int index = 0; index < number_of_clusters; ++index){
        int color = index * color_inc;
        for(const auto &px : cluster_vect[index]->pixels){
            img_out(px.x, px.y) = color;
        }
    }
    */
}

void KMeans::Init(Eigen::MatrixXi &img, int x_min, int x_max, int y_min, int y_max){
    std::default_random_engine x_generator, y_generator;
    std::uniform_int_distribution<int> x_distribution(x_min, x_max);
    std::uniform_int_distribution<int> y_distribution(y_min, y_max);
    auto x_gen = std::bind(x_distribution, x_generator);
    auto y_gen = std::bind(y_distribution, y_generator);
    for(int i = 0; i < number_of_clusters; ++i){
        clusters.at(i).cluster_center.SetCoord(x_gen(), y_gen());
        clusters.at(i).cluster_center.UpdateValue(img);
    }
}

double KMeans::ProcessKMeansStep(Eigen::MatrixXi &img){
    int rows = img.rows();
    int cols = img.cols();

    for(int index = 0; index < number_of_clusters; ++index){
        clusters.at(index).ClearPixels();
        clusters.at(index).total_dist = 0.0;
    }

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            double dist;
            Pixel px(i, j, img(i, j));
            int cluster_index = FindClosestCluster(px, dist);
            clusters.at(cluster_index).pixels.push_back(px);
            clusters.at(cluster_index).total_dist += dist;
        }
    }

    double total_dist(0.0);
    for(int index = 0; index < number_of_clusters; ++index){
        total_dist += clusters.at(index).total_dist;
        int x_mean(0), y_mean(0), n(0);
        for(const auto &px : clusters.at(index).pixels){
            ++n;
            x_mean += px.x;
            y_mean += px.y;
        }
        int x_center = n > 0 ? int(x_mean/n) : clusters.at(index).cluster_center.x;
        int y_center = n > 0 ? int(y_mean/n) : clusters.at(index).cluster_center.y;
        x_center = x_center >= rows ? rows - 1 : x_center;
        x_center = x_center < 0 ? 0 : x_center;
        y_center = y_center >= cols ? cols - 1 : y_center;
        y_center = y_center < 0 ? 0 : y_center;
        clusters.at(index).cluster_center.SetCoord(x_center, y_center);
        clusters.at(index).cluster_center.UpdateValue(img);
    }
    return total_dist;
}

int KMeans::FindClosestCluster(Pixel p, double &dist){
    int cluster_index = 0;
    double min_dist = std::numeric_limits<double>::max();

    for(int i = 0; i < number_of_clusters; ++i){
        double current_dist = distance(p, clusters.at(i).cluster_center);
        if(current_dist < min_dist){
            min_dist = current_dist;
            cluster_index = i;
        }
    }
    dist = min_dist;
    return cluster_index;
}
