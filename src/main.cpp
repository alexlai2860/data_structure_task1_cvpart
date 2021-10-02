/**
 * @file main.cpp
 * @author alex
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * alex all rights reserved
 * 
 */

#include "map_identify.h"
#include <iostream>

using namespace std;

int main()
{
    cv::Mat src;
    Map map1;
    Road road;
    Roads roads;
    Point point1;
    FindShortestPath find1;
    src = cv::imread("002.png");
    map1.src_map = src.clone();
    find1.get_road_img(map1.src_map, map1);
    find1.cvRosenfeld(map1.binary_map, map1.thin_img, map1);
    cv::imshow("dst", map1.thin_img);
    cv::waitKey(200);
    point1.cross_point = find1.cross_point_identify(map1.thin_img, point1);
    for (int i = 0; i < point1.cross_point.size(); i++)
    {
        cv::circle(src, point1.cross_point[i], 2, cv::Scalar(0, 0, 255), 3);
        cv::circle(map1.thin_img, point1.cross_point[i], 14, cv::Scalar(0, 0, 0), -1);
    }
    find1.getRoadLength(src, roads, road, map1);
    cout << point1.cross_point_num << endl;
    cv::imshow("dst2", src);
    cv::imshow("road_image2", map1.thin_img);
    cv::waitKey();
    return 0;
}