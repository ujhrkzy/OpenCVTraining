#pragma once
#include <opencv2/opencv.hpp>

class BinarizationSample {
public:
    BinarizationSample();

    int executeSauvola();
    void sauvolaFast(const cv::Mat &src, cv::Mat &dst, int kernelSize, double k,
            double r);
};
