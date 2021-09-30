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

void FindShortestPath::splitRoad(Road &road, Map &map)
{
    vector<int> x;
    vector<int> y;
    for (int i = 0; i < road.cross_point.size(); i++)
    {
        int x1 = road.cross_point[i].x;
        int y1 = road.cross_point[i].y;
        x.push_back(x1);
        y.push_back(y1);
        int a = x[i] - 5;
        int b = x[i] + 5;
        int c = y[i] - 5;
        int d = y[i] + 5;
        int x_delete, y_delete;
        for (x_delete = a; x_delete < b; x_delete++)
        {
            for (y_delete = c; y_delete < d; y_delete++)
            {
                map.thin_img.at<uchar>(x_delete, y_delete) = 255;
            }
        }
    }
}