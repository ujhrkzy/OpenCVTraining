#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "BinarizationSample.h"

using namespace std;
using namespace cv;

BinarizationSample::BinarizationSample() {
}

int BinarizationSample::executeSauvola() {
    const char *fileName =
            "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/src_room.png";

    cv::Mat src = cv::imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat dst;
    sauvolaFast(src, dst, 11, 0.15, 50);

    cv::imshow("src", src);
    cv::imshow("sauvola integral", dst);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}

void BinarizationSample::sauvolaFast(const cv::Mat &src, cv::Mat &dst,
        int kernelSize, double k, double r) {
    dst.create(src.size(), src.type());

    cv::Mat srcWithBorder;
    int borderSize = kernelSize / 2 + 1;
    int kernelPixels = kernelSize * kernelSize;
    cv::copyMakeBorder(src, srcWithBorder, borderSize, borderSize, borderSize,
            borderSize, cv::BORDER_REPLICATE);

    cv::Mat sum, sqSum;
    cv::integral(srcWithBorder, sum, sqSum);
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            int kx = x + kernelSize;
            int ky = y + kernelSize;
            double sumVal = sum.at<int>(ky, kx) - sum.at<int>(ky, x)
                    - sum.at<int>(y, kx) + sum.at<int>(y, x);
            double sqSumVal = sqSum.at<double>(ky, kx) - sqSum.at<double>(ky, x)
                    - sqSum.at<double>(y, kx) + sqSum.at<double>(y, x);

            double mean = sumVal / kernelPixels;
            double var = (sqSumVal / kernelPixels) - (mean * mean);
            if (var < 0.0)
                var = 0.0;
            double stddev = sqrt(var);
            double threshold = mean * (1 + k * (stddev / r - 1));

            if (src.at < uchar > (y, x) < threshold)
                dst.at < uchar > (y, x) = 0;
            else
                dst.at < uchar > (y, x) = 255;
        }
    }
}
