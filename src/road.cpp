/**
 * @file split_road.cpp
 * @author alex
 * @brief 
 * @version 0.3
 * @date 2021-09-26
 * 
 * alex all rights reserved
 * 
 */

#include "map_identify.h"
#include <iostream>
#include <vector>

using namespace std;

bool FindShortestPath::getRoadLength(cv::Mat &src, Roads &roads, Road &road, Map &map)
{
    vector<cv::Vec4i> hireachy;
    vector<vector<cv::Point>> contours;
    cv::findContours(map.thin_img, contours, hireachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point());
    cv::drawContours(src, contours, -1, cv::Scalar(255, 0, 255));
    for (int i = 0; i < contours.size(); i++)
    {
        double length = cv::arcLength(contours[i], false);
        //if (length > 10)
        //{
        road.length = length / 2;
        road.points = contours[i];
        roads.push_back(road);
        /*vector<cv::Point> contours_i = contours[i];
            for (int j = 0; j < contours_i.size(); j++)
            {
                roads[i].points.push_back(contours_i[j]);
            }*/
        cout << "contourlength:" << roads[i].length << endl;
        cout << "pointstest" << roads[i].points[0].x << endl;
        //}
    }
    cout << "points size" << roads[1].points.size() << endl;
    return contours.size() > 0;
}

int pointDistance(vector<cv::Point> &cross_point, cv::Point &point)
{
    vector<int> distance;
    int nearest_point_num = 0;
    for (int i = 0; i < cross_point.size(); i++)
    {
        int dx = abs(cross_point[i].x - point.x);
        int dy = abs(cross_point[i].y - point.y);
        distance.push_back(dx * dx + dy * dy);
    }
    for (int j = 0; j < distance.size(); j++)
    {
        if (distance[j] < distance[nearest_point_num])
        {
            nearest_point_num = j;
        }
    }
    return nearest_point_num;
}

bool FindShortestPath::getSidePoint(Roads &roads, Map &map, Point &point)
{

    for (int i = 0; i < roads.size(); i++)
    {
        int x1 = 0, x2 = 0, x1_num, x2_num;
        x1 = roads[i].points[1].x;
        x2 = roads[i].points[0].x;
        for (int j = 0; j < roads[i].points.size(); j++)
        {
            if (roads[i].points[j].x < x1)
            {
                x1 = roads[i].points[j].x;
                x1_num = j;
            }
            else if (roads[i].points[j].x > x2)
            {
                x2 = roads[i].points[j].x;
                x2_num = j;
            }
        }
        int left_side_pointnum = pointDistance(point.cross_point, roads[i].points[x1_num]);
        int right_side_pointnum = pointDistance(point.cross_point, roads[i].points[x2_num]);
        roads[i].sidepoint_num[0] = left_side_pointnum;
        roads[i].sidepoint_num[1] = right_side_pointnum;
        cout << "for road " << i << endl;
        cout << "leftside point num :" << left_side_pointnum << " rightside point num :" << right_side_pointnum << endl;
        cout << "length :" << roads[i].length << endl;
    }

    return 1;
}