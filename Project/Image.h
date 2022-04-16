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
	int getInfo(int x, int y, int channels);//��ȡ��Ӧͨ��ͼ������ֵ����
	int getImageInfo(Mat &src);				//
	int biLinear(float x, float y, int channels);//˫���Բ�ֵ����
	double BSpline(int s, double t);			//3��������ֵ���������
	Mat waterWaveTrans(Mat &src, Mat &dst);   //ˮ���ƺ���
	Mat rotateWaveTrans(Mat &src, Mat &dst);  //��ת����
	int BTrans(Mat &dst, vector<Point>mUp, vector<Point>mDown);   //B��������
};

