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

//地图类，主要存放mat类对象
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

//道路类，包括每条道路的两个端点和道路长度
class Road
{
public:
    int sidepoint_num[2];
    int road_num;
    double length;
    vector<cv::Point> points;
    Road() = default;
    ~Road() {}
};

typedef vector<Road> Roads;

//点类，用于查找和存放交叉点
class Point
{
public:
    cv::Point point;
    vector<cv::Point> cross_point;
    int cross_point_num;
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
    vector<cv::Point> cross_point_identify(cv::Mat &thinSrc, Point &point);
    bool getRoadLength(cv::Mat &src, Roads &roads, Road &road, Map &map);
    bool getSidePoint(Roads &roads, Map &map, Point &point);
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