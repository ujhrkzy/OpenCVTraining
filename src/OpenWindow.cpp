/*
 * Sample2.cpp
 *
 *  Created on: 2015/10/04
 *      Author: ujihirokazuya
 */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "OpenWindow.h"

OpenWindow::OpenWindow() {
}

void OpenWindow::execute() {
    // 初期化時に塗りつぶす
    cv::Mat red_img(cv::Size(640, 480), CV_8UC3, cv::Scalar(0, 0, 255));
    cv::Mat white_img(cv::Size(640, 480), CV_8UC3, cv::Scalar::all(255));
    cv::Mat black_img = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3);

    // 初期化後に塗りつぶす
    cv::Mat green_img = red_img.clone();
    green_img = cv::Scalar(0, 255, 0);

    cv::namedWindow("red image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    cv::namedWindow("white image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    cv::namedWindow("black image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    cv::namedWindow("green image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
    cv::imshow("red image", red_img);
    cv::imshow("white image", white_img);
    cv::imshow("black image", black_img);
    cv::imshow("green image", green_img);
    cv::waitKey(0);
}
