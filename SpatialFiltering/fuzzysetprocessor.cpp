#include "fuzzysetprocessor.h"

FuzzySetProcessor::FuzzySetProcessor() :
    number_of_sets(0)
{

}

std::function<double(int)> FuzzySetProcessor::CreateMembershipFunction(MembershipFunctionType type, std::vector<int> key_points){
    std::function<double(int)> membership_function = NULL;
    switch(type){
    case TRIANGULAR:
        if(key_points.size() == 3){
            membership_function = [key_points](int z){
                double res(0.0);
                double a(key_points[0]),
                        b(key_points[1]),
                        c(key_points[2]);
                if(z < a && z >= (a - b)){
                    res = 1.0 - ((double)(a - z))/((double)b);
                }
                else if (z >= a && z <= (a + c)){
                    res = 1.0 - ((double)(z - a))/((double)c);
                }
                return res;
            };
        }
        break;
    case TRAPEZOIDAL:
        if(key_points.size() == 4){
            membership_function = [key_points] (int z){
               double res(0.0);
               double a(key_points[0]),
                       b(key_points[1]),
                       c(key_points[2]),
                       d(key_points[3]);
               if(z >= (a - c) && z < a){
                   res = 1.0 - ((double)(a - z))/((double)c);
               }
               else if (z >= a && z < b){
                   res = 1.0;
               }
               else if (z >= b && z <= (b + d)){
                   res = 1.0 - ((double)(z - b))/((double)d);
               }
               return res;
            };
        }
        break;
    case SIGMA:
        if(key_points.size() == 2){
            membership_function = [key_points] (int z){
               double res(0.0);
               double a(key_points[0]),
                       b(key_points[1]);
               if(z < a && z >= (a - b)){
                   res = 1.0 - ((double)(a - z))/((double)b);
               }
               else if (z > a){
                   res = 1.0;
               }
               return res;
            };
        }
        break;
    case B_SIGMA:
        if(key_points.size() == 2){
            membership_function = [key_points] (int z){
               double res(0.0);
               double a(key_points[0]),
                       b(key_points[1]);
               if(z <= a){
                   res = 1.0;
               }
               else if (z > a && z <= (a + b)){
                   res = 1.0 - ((double)(z-a))/(b);
               }
               return res;
            };
        }
        break;
    case S_SHAPE:
        if(key_points.size() == 3){
            membership_function = [key_points](int z){
                double res(0.0);
                double a(key_points[0]),
                        b(key_points[1]),
                        c(key_points[2]);
                if(z >= a && z <= b){
                    res = 2 * std::pow(((double)(z - a))/((double)(c - a)), 2);
                }
                else if (z > b && z <= c){
                    res = 1.0 - 2 * std::pow(((double)(z - c))/((double)(c - a)), 2);
                }
                else if(z > c){
                    res = 1.0;
                }
                return res;
            };
        }
        break;
    }
    return membership_function;
}

void FuzzySetProcessor::ProcessFuzzySets(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar){
    int rows(img.rows()), cols(img.cols());
    img_out.resize(rows, cols);
    for(int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            std::vector<double> memberships;
            int current_value = img(i, j);
            for(unsigned int k = 0; k < membership_functions.size(); ++k){
                memberships.push_back(membership_functions[k](current_value));
            }
            double output_value(0.0);
            double total_membership(0.0);
            for(unsigned int k = 0; k < memberships.size(); ++k){
                output_value += memberships[k] * output_per_set[k];
                total_membership += memberships[k];
            }
            int output = std::floor(0.5 + output_value/total_membership);
            img_out(i, j) = output;
        }
        if(progress_bar){
            progress_bar->setValue(std::floor(((i+1)*100)/rows));
        }
    }
}
