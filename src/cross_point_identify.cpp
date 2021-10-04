/**
 * @file cross_point_identify.cpp
 * @author alex
 * @brief 定义两个函数（求两点距离及求交点）(心力交瘁)
 * @version 0.２
 * @date 2021-09-26
 * 
 * alex all rights reserved
 * 
 */

#include "map_identify.h"
#include <iostream>

using namespace std;

double FindShortestPath::get_distance(cv::Point2f &a, cv::Point2f &b)
{
	double distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return distance;
}

//交叉点检测
vector<cv::Point> FindShortestPath::cross_point_identify(cv::Mat &thinSrc, Point &point1)
{
	unsigned int raudis = 4, raudis2 = 15;
	unsigned int thresholdMax = 12;
	unsigned int thresholdMin = 0;
	int width = thinSrc.cols;
	int height = thinSrc.rows;
	cv::Mat tmp, tmp2;
	point1.cross_point_num = 0;
	thinSrc.copyTo(tmp);
	thinSrc.copyTo(tmp2);
	vector<cv::Point> points;
	vector<cv::Point> points2;
	//从原点开始遍历
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			//若当前点的值为０，则继续寻找下一个点
			if (*(tmp.data + tmp.step * i + j) == 0)
			{
				continue;
			}
			point1.count = 0;
			//在白色像素点周围2r*2r的区域内搜索白色像素点，并累加数量
			for (int k = i - raudis; k < i + raudis + 1; k++)
			{
				for (int l = j - raudis; l < j + raudis + 1; l++)
				{
					if (k < 0 || l < 0 || k > height - 1 || l > width - 1)
					{
						continue;
					}
					else if (*(tmp.data + tmp.step * k + l) == 255)
					{
						point1.count++;
					}
				}
			}
			//当区域内白色像素点数符合阈值条件时
			if (point1.count > thresholdMax || point1.count < thresholdMin)
			{
				point1.point = cv::Point(j, i);

				//对其相邻区域像素点逐一进行白色像素点搜索操作，
				for (int j2 = j - raudis2; j2 < j + raudis2 + 1; j2++)
				{
					for (int i2 = i - raudis2; i2 < i + raudis2 + 1; i2++)
					{
						if (*(tmp2.data + tmp2.step * i2 + j2) == 0)
						{
							continue;
						}
						int count = 0;
						for (int k2 = i2 - raudis; k2 < i2 + raudis + 1; k2++)
						{
							for (int l2 = j2 - raudis; l2 < j2 + raudis + 1; l2++)
							{
								if (k2 < 0 || l2 < 0 || k2 > height - 1 || l2 > width - 1)
								{
									continue;
								}
								else if (*(tmp2.data + tmp2.step * k2 + l2) == 255)
								{
									count++;
								}
							}
						}
						//若相邻区域内有像素点的区域内白色像素点数大于原先的点（有点绕口）
						if (count >= point1.count)
						{
							//更新原先的点
							point1.point = cv::Point(j2, i2);
							point1.count = count;
						}
					}
				}
				//若容器不为空，则判断后插入vector
				if (points.size() != 0)
				{
					bool accept = 1;
					for (int n = 0; n < points.size(); n++)
					{
						int x = points[n].x;
						int y = points[n].y;
						if (point1.point.x == x && point1.point.y == y)
						{
							accept = 0;
							break;
						}
					}
					if (accept)
					{
						points.push_back(point1.point);
						point1.cross_point_num++;
						cout << point1.point.x << " " << point1.point.y << endl;
					}
				}
				else
				{
					points.push_back(point1.point);
				}
			}
		}
	}
	return points;
}