#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "FaceDetectionSample.h"

using namespace std;
using namespace cv;

FaceDetectionSample::FaceDetectionSample() {
}

int FaceDetectionSample::execute() {
    const char *fileName =
            "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/src_people.png";
    Mat image = imread(fileName);

    //分類器（カスケード）の指定
    const cv::String cascade_file =
            "/Users/ujihirokazuya/Documents/opencv/library/3.0/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
    CascadeClassifier cascade;
    cascade.load(cascade_file);

    vector < Rect > faces;
    cascade.detectMultiScale(image, faces, 1.1, 3, 0, Size(20, 20));

    for (int i = 0; i < faces.size(); i++) {
        rectangle(image, Point(faces[i].x, faces[i].y),
                Point(faces[i].x + faces[i].width,
                        faces[i].y + faces[i].height), Scalar(0, 200, 0), 3,
                CV_AA);
    }
    imshow("detect face", image);
    waitKey(0);

    return 0;
}
