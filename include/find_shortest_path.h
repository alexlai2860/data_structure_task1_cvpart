#pragma once

#include "map_identify.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct EdgeNode
{
    //顶点对应的下标
    int adjvex;
    //权值
    int weight;
    //指向下一个邻接点
    struct EdgeNode *next;
} edgeNode;

//顶点表结点
typedef struct VertexNode
{
    //顶点数据
    char data[50];
    //边表头指针
    edgeNode *firstedge;
} VertexNode, AdjList[100];

//集合
typedef struct
{
    AdjList adjList;
    //顶点数和边数
    int numVertexes, numEdges;
} GraphAdjList;

class AdjacencyList
{
public:
    //存储具体路径
    int ShortestPathmatrix[100][100] = {0};
    //存储最短路径值
    double ShortestPathvalue[100][100] = {0.0};
    //距离信息,_distance[0][1] = 50;代表从下标为0到下表为1地点距离为50
    double _distance[100][100] = {0.0};

    void ShowALGraph(GraphAdjList *G);
    void Test();
    //初始化地图
    void InitMap(GraphAdjList *G, Roads &roads, Point &point);
    //创建地图
    void CreateALGraph(GraphAdjList *G);
    //计算各个顶点之间最短路径
    void ShortestPath_Floyd(GraphAdjList *G, int (&P)[100][100], double (&D)[100][100]);
    //输出路径长度和具体路径
    void ShowShortestResult(cv::Mat &src, cv::Mat &thinimg, Roads &roads, int originPos, int endPos);
    AdjacencyList() = default;
    ~AdjacencyList() {}
};