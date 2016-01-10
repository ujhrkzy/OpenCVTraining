#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "BackProjectionSample.h"

BackProjectionSample::BackProjectionSample() {
}

//int main(int argc, char **argv) {
int BackProjectionSample::execute() {
    int i, hist_size = 90;
    float h_ranges[] = { 0, 181 };
    float *ranges[] = { h_ranges };
    double min_val, max_val;
    CvSize dst_size;
    CvPoint min_loc, max_loc;
    IplImage *src_img, *tmp_img, *dst_img;
    IplImage *src_hsv, *tmp_hsv;
    IplImage **src_planes, *tmp_planes[3];
    CvHistogram *hist = 0;

//    if (argc != 3 || (src_img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR)) == 0
//            || (tmp_img = cvLoadImage(argv[2], CV_LOAD_IMAGE_COLOR)) == 0) {
//        return -1;
//    }
    src_img =
            cvLoadImage(
                    "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/src_people.png",
                    CV_LOAD_IMAGE_COLOR);
    tmp_img =
            cvLoadImage(
                    "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/tmp_people.png",
                    CV_LOAD_IMAGE_COLOR);

    src_planes = (IplImage **) cvAlloc(sizeof(IplImage *) * 3);
    for (i = 0; i < 3; i++) {
        src_planes[i] = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
        tmp_planes[i] = cvCreateImage(cvGetSize(tmp_img), IPL_DEPTH_8U, 1);
    }

    // (1)2つ入力画像（探索画像，テンプレート画像）の色空間を，RGBからHSVに変換
    // RGBではなく、HSV色空間でのマッチングを実施。
    // （RGBと比較して、HSV色空間は人間の色の認識と親和性があり、色相と彩度の組み合わせは照明変化に対して変化が少ないため。）
    // キャプチャされた画像に対してH（Hue：色相）とS（Saturation：彩度）のレンジが近い領域を、
    // テンプレート画像にマッチしている領域として検出している。
    src_hsv = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
    tmp_hsv = cvCreateImage(cvGetSize(tmp_img), IPL_DEPTH_8U, 3);
    cvCvtColor(src_img, src_hsv, CV_BGR2HSV);
    cvCvtColor(tmp_img, tmp_hsv, CV_BGR2HSV);
    // cvSplit equals cvCvtPixToPlane
    cvSplit(src_hsv, src_planes[0], src_planes[1], src_planes[2], 0);
    cvSplit(tmp_hsv, tmp_planes[0], tmp_planes[1], tmp_planes[2], 0);

    // (2)テンプレート画像のヒストグラムを計算
    hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
    cvCalcHist(&tmp_planes[0], hist, 0, 0);
    // (3)探索画像全体に対して，テンプレートのヒストグラムとの距離（手法に依存）を計算
    dst_size = cvSize(src_img->width - tmp_img->width + 1,
            src_img->height - tmp_img->height + 1);
    dst_img = cvCreateImage(dst_size, IPL_DEPTH_32F, 1);
    cvCalcBackProjectPatch(src_planes, dst_img, cvGetSize(tmp_img), hist,
            CV_COMP_CORREL, 1.0);
    cvMinMaxLoc(dst_img, &min_val, &max_val, &min_loc, &max_loc, NULL);
    // (4)テンプレートに対応する位置に矩形を描画
    cvRectangle(src_img, max_loc,
            cvPoint(max_loc.x + tmp_img->width, max_loc.y + tmp_img->height),
            CV_RGB(255, 0, 0), 3);

    cvNamedWindow("Image", 1);
    cvShowImage("Image", src_img);
    cvWaitKey(0);

    cvDestroyWindow("Image");
    cvReleaseImage(&src_img);
    cvReleaseImage(&dst_img);
    cvReleaseImage(&tmp_img);
    cvReleaseImage(&src_hsv);
    cvReleaseImage(&tmp_hsv);
    for (i = 0; i < 3; i++) {
        cvReleaseImage(&src_planes[i]);
        cvReleaseImage(&tmp_planes[i]);
    }
    cvFree(&src_planes);

    return 0;
}
