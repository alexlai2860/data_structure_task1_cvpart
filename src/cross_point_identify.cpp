/**
 * @file cross_point_identify.cpp
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

vector<cv::Point> FindShortestPath::cross_point_identify(cv::Mat &thinSrc, Road &road)
{
	unsigned int raudis = 6;
	unsigned int thresholdMax = 16;
	unsigned int thresholdMin = 0;
	int width = thinSrc.cols;
	int height = thinSrc.rows;
	cv::Mat tmp;
	road.cross_point_num = 0;
	thinSrc.copyTo(tmp);
	vector<cv::Point> points;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (*(tmp.data + tmp.step * i + j) == 0)
			{
				continue;
			}
			int count = 0;
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
						count++;
					}
				}
			}

			if (count > thresholdMax || count < thresholdMin)
			{
				cv::Point point(j, i);
				points.push_back(point);
				road.cross_point_num++;
			}
		}
	}
	return points;
}