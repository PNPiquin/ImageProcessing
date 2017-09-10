#ifndef FUZZYSETPROCESSOR_H
#define FUZZYSETPROCESSOR_H

#include <Eigen/Dense>
#include <QProgressBar>

class FuzzySetProcessor
{
public:
    FuzzySetProcessor();

    enum MembershipFunctionType { TRIANGULAR, TRAPEZOIDAL, SIGMA, B_SIGMA, S_SHAPE }; // B_SIGMA --> 1 - SIGMA

    //void SetNumberOfSets(int n) {number_of_sets = n;}
    void PushMembershipFunction(std::function<double(int)> func, int output_for_func) {
        membership_functions.push_back(func);
        output_per_set.push_back(output_for_func);
        number_of_sets++;
    }

    void ProcessFuzzySets(Eigen::MatrixXi &img, Eigen::MatrixXi &img_out, QProgressBar *progress_bar=NULL);

    static std::function<double(int)> CreateMembershipFunction(MembershipFunctionType type, std::vector<int> key_points);


private:
    int number_of_sets;
    std::vector<std::function<double(int)>> membership_functions;
    std::vector<int> output_per_set;
};

#endif // FUZZYSETPROCESSOR_H
