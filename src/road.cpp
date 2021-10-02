/**
 * @file split_road.cpp
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

bool FindShortestPath::getRoadLength(cv::Mat &src, Roads &roads, Road &road, Map &map)
{
    vector<cv::Vec4i> hireachy;
    vector<vector<cv::Point>> contours;
    cv::findContours(map.thin_img, contours, hireachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point());
    cv::drawContours(src, contours, -1, cv::Scalar(255, 0, 255));
    for (int i = 0; i < contours.size(); i++)
    {
        roads.push_back(road);
        double length = cv::arcLength(contours[i], false);
        if (length > 10)
        {
            roads[i].length = length / 2;
            roads[i].road = contours[i];
            cout << "contourlength:" << roads[i].length << endl;
        }
    }
    return contours.size() > 0;
}

bool pointDistance(vector<cv::Point> &cross_point,cv::Point &point)
{

}

bool FindShortestPath::getSidePoint(Roads &roads, Map &map, Point &point)
{

    for (int i = 0; i < roads.size(); i++)
    {
        int x1, x2, x1_num, x2_num;
        x1 = roads[i].road[0].x;
        x2 = roads[i].road[0].x;
        for (int j = 0; j < roads[i].road.size(); j++)
        {
            if (roads[i].road[j].x < x1)
            {
                x1 = roads[i].road[j].x;
                x1_num = j;
            }
            else if(roads[i].road[j].x > x2)
            {
                x2 = roads[i].road[j].x;
                x2_num = j;
            }
        }
    }
    return 1;
}