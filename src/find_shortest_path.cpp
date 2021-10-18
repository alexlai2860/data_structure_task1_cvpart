#include "find_shortest_path.h"
#include "map_identify.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace std;
//边表结点

//创建地图
void AdjacencyList::CreateALGraph(GraphAdjList *G)
{
    edgeNode *e; /* 
    //读入顶点信息，建立顶点表
    for (int i = 0; i < G->numVertexes; i++)
    {
        //读入顶点信息
        strcpy(G->adjList[i].data, _mapName[i]);
        //将边表置为空表
        G->adjList[i].firstedge = NULL;
    } */
    //建立边表（头插法）
    for (int i = 0; i < G->numVertexes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int temp;
            if (this->_distance[i][j] != 0 || this->_distance[j][i] != 0)
            {
                if (this->_distance[i][j] != 0)
                {
                    temp = this->_distance[i][j];
                    this->_distance[j][i] = this->_distance[i][j];
                }
                else
                {
                    temp = _distance[j][i];
                    this->_distance[i][j] = this->_distance[j][i];
                }
                e = new EdgeNode;
                e->adjvex = j;
                e->next = G->adjList[i].firstedge;
                e->weight = temp;
                G->adjList[i].firstedge = e;

                e = new EdgeNode;

                e->adjvex = i;
                e->next = G->adjList[j].firstedge;
                e->weight = temp;
                G->adjList[j].firstedge = e;
            }
        }
    }
}

void AdjacencyList::Test()
{
    cout << "ALL IS OK." << endl;
}

void AdjacencyList::ShowALGraph(GraphAdjList *G)
{
    for (int i = 0; i < G->numVertexes; i++)
    {
        cout << "顶点" << i << ": " << G->adjList[i].data << "--firstedge--";
        edgeNode *p = new edgeNode;
        p = G->adjList[i].firstedge;
        while (p)
        {
            cout << p->adjvex << "--Weight: " << p->weight << "--Next--";
            p = p->next;
        }
        cout << "--NULL" << endl;
    }
}

//初始化地图基本数据
void AdjacencyList::InitMap(GraphAdjList *G, Roads &roads, Point &point)
{
    //输入顶点数和边数
    G->numVertexes = point.cross_point_num;
    G->numEdges = roads.size();

    for (int k = 0; k < roads.size(); k++)
    {
        for (int i = 0; i < point.cross_point_num; i++)
        {
            for (int j = 0; j < point.cross_point_num; j++)
            {
                int num1 = roads[k].sidepoint_num[0];
                int num2 = roads[k].sidepoint_num[1];
                if (num1 == i && num2 == j)
                {
                    this->_distance[i][j] = roads[k].length;
                }
                else if (num2 == i && num2 == j)
                {
                    this->_distance[i][j] = roads[k].length;
                }
            }
        }
    }
    /* cout << this->_distance[7][4] << endl;
    cout << this->_distance[14][19] << endl;
    cout << this->_distance[0][2] << endl; */
}

void AdjacencyList::ShortestPath_Floyd(GraphAdjList *G, int (&P)[100][100], double (&D)[100][100])
{
    //初始化D与P
    for (int v = 0; v < G->numVertexes; ++v)
    {
        for (int w = 0; w < G->numVertexes; ++w)
        {
            if (this->_distance[v][w] == 0 && v != w)
            {
                this->_distance[v][w] = 10000;
            }
            D[v][w] = this->_distance[v][w];
            P[v][w] = w;
        }
    }
    for (int k = 0; k < G->numVertexes; ++k)
    {
        for (int v = 0; v < G->numVertexes; ++v)
        {
            for (int w = 0; w < G->numVertexes; ++w)
            {
                if (D[v][w] > D[v][k] + D[k][w])
                {
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];
                }
            }
        }
    }
    cout << G->numVertexes << endl;
    cout << P[24][7] << endl;
    cout << D[24][7] << endl;
}

void AdjacencyList::ShowShortestResult(cv::Mat &src, cv::Mat &thinimg, Roads &roads, Point &point, int originPos, int endPos)
{
    cv::Mat src2 = src.clone();

    cv::imshow("test", src2);
    // vector<cv::Vec4i> hireachy;
    // vector<vector<cv::Point>> contours;
    // cv::findContours(thinimg, contours, hireachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point());
    std::vector<int> way_points;
    int temp;
    cout << "地点" << originPos << "到地点" << endPos << "最短距离为" << this->ShortestPathvalue[originPos][endPos] << endl;
    temp = ShortestPathmatrix[originPos][endPos];
    cout << "具体路径为：" << originPos << "——>";
    while (temp != endPos)
    {
        way_points.push_back(temp);
        cv::circle(src2,point.cross_point[temp], 3, cv::Scalar(0, 255, 0), 4);
        cout << temp << "——>";
        temp = ShortestPathmatrix[temp][endPos];
    }
    cout << endPos << endl;
    cv::circle(src2,point.cross_point[endPos], 3, cv::Scalar(0, 255, 0), 4);
    way_points.push_back(endPos);
    for (int i = 0; i + 1 < way_points.size(); i++)
    {
        for (int j = 0; j < roads.size(); j++)
        {
            int num1 = roads[j].sidepoint_num[0];
            int num2 = roads[j].sidepoint_num[1];
            if (num1 == way_points[i] && num2 == way_points[i + 1])
            {
                vector<cv::Point> temp = roads[j].points;
                vector<vector<cv::Point>> temp2;
                temp2.push_back(temp);
                cv::drawContours(src2, temp2, -1, cv::Scalar(0, 225, 255), 3);
                //cv::drawContours(src, contours, j, cv::Scalar(0, 0, 255), 3);
            }
            else if (num2 == way_points[i] && num1 == way_points[i + 1])
            {
                vector<cv::Point> temp = roads[j].points;
                vector<vector<cv::Point>> temp2;
                temp2.push_back(temp);
                cv::drawContours(src2, temp2, -1, cv::Scalar(0, 225, 255), 3);
                //cv::drawContours(src, contours, j, cv::Scalar(0, 0, 255), 3);
            }
        }
    }
    cv::imshow("new", src2);
}