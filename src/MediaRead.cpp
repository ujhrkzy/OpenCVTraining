#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "MediaRead.h"

using namespace cv;
using namespace std;

MediaRead::MediaRead() {
}

void MediaRead::readImage() {
    Mat image = imread("uma.jpeg");
    namedWindow("hoge");
    imshow("hoge", image);
    waitKey(0);
}

void MediaRead::readVideo() {
    //動画の読み込み
    VideoCapture video("uma.mp4");

    //動画を再生する。
    namedWindow("hoge");
    while (1) {
        Mat frame;
        video >> frame;
        //フレームが空か、ボタンが押された時か一周したときに出る。
        if (frame.empty() || waitKey(30) >= 0
                || video.get(CV_CAP_PROP_POS_AVI_RATIO) == 1) {
            break;
        }
        imshow("hoge", frame);
    }
}
