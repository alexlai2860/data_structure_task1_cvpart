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

#include "find_shortest_path.h"
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
    point1.cross_point = find1.cross_point_identify(map1.thin_img, point1); //寻找交叉点
    for (int i = 0; i < point1.cross_point.size(); i++)
    {
        cv::circle(src, point1.cross_point[i], 2, cv::Scalar(0, 0, 255), 3);           //在原图上标注交叉点
        cv::circle(map1.thin_img, point1.cross_point[i], 14, cv::Scalar(0, 0, 0), -1); //利用circle来分割各段道路
    }
    // cv::circle(src, point1.cross_point[11], 2, cv::Scalar(0, 255, 0), 3);
    find1.getRoadLength(src, roads, road, map1);
    find1.getSidePoint(roads, map1, point1);
    //test
    cv::circle(src, point1.cross_point[24], 2, cv::Scalar(0, 255, 0), 3);
    cv::circle(src, point1.cross_point[7], 2, cv::Scalar(0, 255, 0), 3);
    //find1.delete_longer_road(roads);
    cout << roads.size() << endl;
    cout << point1.cross_point_num << endl;

    cv::imshow("dst2", src);
    cv::imshow("road_image2", map1.thin_img);
    cv::waitKey(1000);

    //以下为最短路径的算法部分
    AdjacencyList adjacencyList;
    int originPos, endPos;
    GraphAdjList *GA = new GraphAdjList;
    adjacencyList.Test();
    adjacencyList.InitMap(GA, roads, point1);
    adjacencyList.CreateALGraph(GA);
    adjacencyList.ShortestPath_Floyd(GA, adjacencyList.ShortestPathmatrix, adjacencyList.ShortestPathvalue);
    cout << "请输入第一个点的序号: " << endl;
    cin >> originPos;
    cout << "终点" << endl;
    cin >> endPos;
    adjacencyList.ShowShortestResult(src, map1.thin_img, roads, originPos, endPos);
    cv::imshow("result", src);
    cv::waitKey();
    return 0;
}