#include "PlaneFitting.h"
#include <iostream>
#include <random>

int main(int argc, char ** argv)
{
    // data generation
    double a = -1/3.0, b = -2/3.0, d =3.0;
    double w_sigma = 0.1;

    std::vector<float> point_cloud;
    float *center = new float[6];

    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister 19937 生成器
    std::normal_distribution<double> dist(0.0, 1.0);

    for(int i=0; i<30; i++)
    {
        for(int j=0; j<40; j++)
        {
            double x = double(i);
            double y = double(j);
            double z = a*x + b*y + d + dist(gen)*w_sigma;
            point_cloud.push_back(x);
            point_cloud.push_back(y);
            point_cloud.push_back(z);
        }
    }

    // perform Plane Fitting Algorithm
    bool ret = PlaneFitting(point_cloud.data(), point_cloud.size(), 0.1, 100, center);

    for(int i=0; i<6; i++)
    {
        std::cout << center[i] << std::endl;
    }

    std::cout << "Hollo world." << std::endl;

    return 0;
}







