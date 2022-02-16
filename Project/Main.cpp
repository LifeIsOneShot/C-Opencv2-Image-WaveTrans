#include<iostream>
#include "Image.h"
#include "wave.h"
using namespace std;

Image image;
Mat BT;

int main()
{
	Mat Readimage, wave, rote;

	Readimage = imread("../img/lena.jpg");//read image
	BT = Readimage.clone();
	
	image.getImageInfo(Readimage);//get image information

	// main algorithm
	showWave(image, Readimage, wave, rote, BT);

	// press 's' to stop
	cout<<"************************************************"<<endl;
	cout<<"************************************************"<<endl;
	cout<<"Press s to stop"<<endl; 
	cout<<"************************************************"<<endl;
	cout<<"************************************************"<<endl;
	while ( waitKey() != 's'){}
	return 0;
}
