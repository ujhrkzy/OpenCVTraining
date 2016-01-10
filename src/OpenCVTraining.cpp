#include "OpenWindow.h"
#include "BackProjectionSample.h"
#include "HistogramSample2.h"
#include "EdgeDetectionSample.h"
#include "BinarizationSample.h"
#include "FaceDetectionSample.h"

int main(int argc, char **argv) {
//    BackProjectionSample target;
//    target.execute();
//    HistogramSample2 target;
//    target.execute(argc, argv);
//    EdgeDetectionSample target;
//    target.execute();
//    BinarizationSample target;
//    target.executeSauvola();
    FaceDetectionSample target;
    target.execute();
}
