#include<iostream>
#include "Image.h"
#include "wave.h"
using namespace std;

Image image;
Mat BT;

int main()
{
	while (1) {
		Mat Readimage, wave, rote;

		Readimage = imread("../img/lena.jpg");//read image
		resize(Readimage, Readimage, Size(800, 800));
		BT = Readimage.clone();

		image.getImageInfo(Readimage);//get image information

		// main algorithm
		showWave(image, Readimage, wave, rote, BT);
	}
	// press 's' to stop
	cout<<"************************************************"<<endl;
	cout<<"************************************************"<<endl;
	cout<<"Press s to stop"<<endl; 
	cout<<"************************************************"<<endl;
	cout<<"************************************************"<<endl;
	while ( waitKey() != 's'){}
	return 0;
}
