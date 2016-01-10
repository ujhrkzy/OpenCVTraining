#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "EdgeDetectionSample.h"

using namespace std;
using namespace cv;

EdgeDetectionSample::EdgeDetectionSample() {
}

int EdgeDetectionSample::execute() {
    Mat img =
            imread(
                    "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/src_room.png",
                    0);
    Mat sobel_img, laplacian_img, canny_img, temp_img;

    //Sobel
    Sobel(img, temp_img, CV_32F, 1, 1);
    convertScaleAbs(temp_img, sobel_img, 1, 0);

    //Laplacian
    Laplacian(img, temp_img, CV_32F, 3);
    convertScaleAbs(temp_img, laplacian_img, 1, 0);

    //Canny
    Canny(img, canny_img, 50, 200);

    imshow("original_image", img);
    imshow("sobel_img", sobel_img);
    imshow("laplacian_img", laplacian_img);
    imshow("canny_img", canny_img);

    waitKey(0);
    return 0;
}
