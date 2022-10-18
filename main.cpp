#include <vector>
#include <iostream>

#include "GaussianFilter.hpp"

int main()
{
    GaussianFilter filter(5, 1.f);
    std::vector<float> out = filter.apply({1.0, 2.0, 3.0, 4.0, 5.0});

    std::cout << "[";
    for(size_t i = 0; i < out.size(); i++)
    {
        std::cout << out[i] << ", ";
    }

    std::cout << "]" << std::endl;
}
