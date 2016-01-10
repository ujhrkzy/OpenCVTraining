#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "HistogramSample.h"

HistogramSample::HistogramSample() {
}

//int main(int argc, char *argv[]) {
int HistogramSample::execute(int argc, char *argv[]) {
    IplImage* src;
    if (argc != 2 || (src = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR)) == 0) {
        return -1;
    }
    // HSV画像を計算し、それを別々のプレーンに分割する。
    CvSize srcSize = cvGetSize(src);
    IplImage* hsv = cvCreateImage(srcSize, 8, 3);
    cvCvtColor(src, hsv, CV_BGR2HSV);

    IplImage* h_plane = cvCreateImage(srcSize, 8, 1);
    IplImage* s_plane = cvCreateImage(srcSize, 8, 1);
    IplImage* v_plane = cvCreateImage(srcSize, 8, 1);
    //  IplImage* planes[] = { h_plane, s_plane };
    cvSplit(hsv, h_plane, s_plane, v_plane, 0);

    // create histogram
    int h_bins = 30;
    int s_bins = 32;
    CvHistogram* hist;
    {
        int hist_size[] = { h_bins, s_bins };
        float h_ranges[] = { 0, 180 };
        float s_ranges[] = { 0, 255 };
        float* ranges[] = { h_ranges, s_ranges };
        hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
    }
    return 0;
}
