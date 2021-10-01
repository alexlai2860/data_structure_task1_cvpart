/**
 * @file map_identify.h
 * @author alex
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * alex all rights reserved
 * 
 */

#pragma once

#include <opencv2/imgproc/types_c.h>
#include <opencv2/opencv.hpp>

using namespace std;

class Map
{
public:
    cv::Mat src_map;
    cv::Mat binary_map;
    cv::Mat thin_img;
    cv::Mat road_img;
    Map() = default;
    ~Map() {}
};

class Road
{
public:
    cv::Point sidepoint[2];
    int road_num;
    int cross_point_num;
    int length;
    vector<cv::Point> cross_point;
    vector<cv::Point> road;
    Road() = default;
    ~Road() {}
};

typedef vector<Road> Roads;

class Point
{
public:
    cv::Point point;
    int count;
    Point() = default;
    ~Point() {}
};

typedef vector<Point> points;

class FindShortestPath
{
public:
    double get_distance(cv::Point2f &a, cv::Point2f &b);
    void get_road_img(cv::Mat &src, Map &map);
    void cvRosenfeld(cv::Mat &src, cv::Mat &dst, Map &map);
    vector<cv::Point> cross_point_identify(cv::Mat &thinSrc, Road &road, Point &point);
    void splitRoad(Road &road, Map &map);
    bool find_shortest_path(cv::Point2f &p1, cv::Point2f &p2);
    FindShortestPath() = default;
    ~FindShortestPath() {}
};

class ShowFinalImg
{
public:
    bool show_final_img();
    ShowFinalImg() = default;
    ~ShowFinalImg() {}
};