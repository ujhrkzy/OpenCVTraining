#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "HistogramSample2.h"

using namespace std;
using namespace cv;

HistogramSample2::HistogramSample2() {
}

//int main(int argc, char *argv[]) {
int HistogramSample2::execute(int argc, char *argv[]) {
    Mat image;
    image =
            cv::imread(
                    "/Users/ujihirokazuya/Documents/workspace/opencv/OpenCVTraining/res/tmp_people.png");
    int index = 32;
    vector < vector<int> > histogram(3);

    for (int i = 0; i < 3; i++) {
        vector<int> hist(255 / index + 1);
        fill(hist.begin(), hist.end(), 0);
        histogram[i] = hist;
    }

    for (int height = 0; height < image.rows; height++) {
        for (int width = 0; width < image.cols; width++) {
            int blue_pixel = image.data[height * image.step
                    + width * image.elemSize() + 0];
            histogram[0][calcIndex(blue_pixel, index)]++;
            int green_pixel = image.data[height * image.step
                    + width * image.elemSize() + 1];
            histogram[1][calcIndex(green_pixel, index)]++;
            int red_pixel = image.data[height * image.step
                    + width * image.elemSize() + 2];
            histogram[2][calcIndex(red_pixel, index)]++;
        }
    }
    for (int i = 0; i < histogram.size(); i++) {
        for (int j = 0; j < histogram[i].size(); j++) {
            cout << j << " " << histogram[i][j] << endl;
        }
    }
    return 0;
}

int HistogramSample2::calcIndex(int pixel, int index) {
    return pixel / index;
}

