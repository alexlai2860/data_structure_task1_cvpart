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
    cv::Mat src_map;    //原图
    cv::Mat binary_map; //二值化图像，用于提取道路
    cv::Mat thin_img;   //细化(骨骼化)图像，用于细化道路
    cv::Mat road_img;   //最终的输出图像
    Map() = default;
    ~Map() {}
};

//道路类，包括每条道路的两个端点和道路长度
class Road
{
public:
    int sidepoint_num[2];     //道路端点
    double length;            //道路长度
    vector<cv::Point> points; //每条道路的轮廓
    Road() = default;
    ~Road() {}
};

typedef vector<Road> Roads;

//点类，用于查找和存放交叉点
class Point
{
public:
    cv::Point point;
    vector<cv::Point> cross_point; //交叉点类
    int cross_point_num;           //计算交叉点数量
    int count;                     //用于累计和比较像素点周边白色像素点数量
    Point() = default;
    ~Point() {}
};

typedef vector<Point> points;

//求最短路径类
class FindShortestPath
{
public:
    double get_distance(cv::Point2f &a, cv::Point2f &b);                    //求两点距离
    void get_road_img(cv::Mat &src, Map &map);                              //求道路图像，即获得二值图
    void cvRosenfeld(cv::Mat &src, cv::Mat &dst, Map &map);                 //细化算法
    vector<cv::Point> cross_point_identify(cv::Mat &thinSrc, Point &point); //交叉点检测算法
    bool getRoadLength(cv::Mat &src, Roads &roads, Road &road, Map &map);   //获取道路长度
    bool getSidePoint(Roads &roads, Map &map, Point &point);                //获取端点
    bool find_shortest_path(cv::Point2f &p1, cv::Point2f &p2);              //获取最短路径(暂未定义)
    FindShortestPath() = default;
    ~FindShortestPath() {}
};

//输出图像类，还没用上
class ShowFinalImg
{
public:
    bool show_final_img();
    ShowFinalImg() = default;
    ~ShowFinalImg() {}
};