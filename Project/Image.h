#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;
class Image
{
private:
	Mat m_ori;
	int m_width;
	int m_height;
	int m_channals;
public:
	Image();
	~Image();
	int getInfo(int x, int y, int channels);//获取对应通道图像像素值函数
	int getImageInfo(Mat &src);				//
	int biLinear(float x, float y, int channels);//双线性插值函数
	double BSpline(int s, double t);			//3次样条插值径向基函数
	Mat waterWaveTrans(Mat &src, Mat &dst);   //水波纹函数
	Mat rotateWaveTrans(Mat &src, Mat &dst);  //旋转函数
	int BTrans(Mat &dst, vector<Point>mUp, vector<Point>mDown);   //B样条函数
};

