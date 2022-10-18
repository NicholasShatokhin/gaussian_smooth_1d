/*
 * Gaussian 1-d smoothing filter
 *
 * @copyright © 2020 Mykola Shatokhin
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI           3.14159265358979323846f  /* pi */
#endif

class GaussianFilter
{
public:
    GaussianFilter(int kernel_size, float sigma)
    {
        m_kernel = prepare_kernel(kernel_size, sigma);
    }

    std::vector<float> apply(std::vector<float> vector)
    {
        std::vector<float> out;

        size_t kernelSide = m_kernel.size() / 2;

        for (size_t i = 0; i < kernelSide; i++)
        {
            vector.insert(vector.begin(), vector[0]);
            vector.push_back(vector[vector.size()-1]);
        }

        size_t ubound = vector.size();
        size_t vectorIndex;
        float smoothed;

        for (size_t i = kernelSide; i < ubound - kernelSide; i++)
        {
            smoothed = 0;

            for(size_t j = 0; j < m_kernel.size(); j++)
            {
                vectorIndex = i + j - kernelSide;

                smoothed += m_kernel[j] * vector[vectorIndex];
            }

            out.push_back(smoothed);
        }
        return out;
    }

private:
    std::vector<float> prepare_kernel(int kernel_size, float sigma)
    {
        std::vector<float> v;

        bool doubleCenter = false;
        if (kernel_size % 2 == 0) {
            doubleCenter = true;
            kernel_size--;
        }
        int steps = (kernel_size - 1) / 2;

        for (int i = steps; i >= 1; i--) {
            v.push_back(gaussian(sigma, - i));
        }

        v.push_back(gaussian(sigma, 0));
        if (doubleCenter) {
            v.push_back(gaussian(sigma, 0));
        }

        for (int i = 1; i <= steps; i++) {
            v.push_back(gaussian(sigma, i));
        }

        return v;
    }

    float gaussian(float sigma, int value)
    {
        return (1.f / std::sqrtf(2.f * M_PI * sigma) * std::expf(-(value * value) / (2.f * sigma * sigma)));
    }

private:
    std::vector<float> m_kernel;
};
