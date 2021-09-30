/**
 * @file get_road_img.cpp
 * @author alex
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * alex all rights reserved
 * 
 */

#include"map_identify.h"
#include <iostream>

using namespace std;

void FindShortestPath::get_road_img(cv::Mat &src,Map &map)
{
    cv::Mat binary_img;
    cv::Scalar low = cv::Scalar(215, 245, 245);
    cv::Scalar high = cv::Scalar(235, 255, 255);
    cv::inRange(src, low, high, binary_img);
    //cv::imshow("img1", binary_img);
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(11, 11));
    cv::dilate(binary_img, binary_img, element);
    //cv::imshow("img2", binary_img);
    cv::waitKey(100);
    map.binary_map = binary_img;
};