#include "wave.h"
#include "mouse.h"

void showWave(Image image, Mat Readimage, Mat wave, Mat rote, Mat BT) {
	Mat img = Readimage.clone();
	namedWindow("picture editor");				
	imshow("picture editor", img);
	
	while (1) {
		int key = waitKey(1);
		if (key == '1')
		{
			image.rotateWaveTrans(Readimage, img);		//회전
			imshow("picture editor", img);
		}
		else if (key == '2')
		{
			image.waterWaveTrans(Readimage, img);		//물결 파동
			imshow("picture editor", img);
		}
		else if (key == '3')
		{						
			imshow("picture editor", img); //B형 파동
			setMouseCallback("picture editor", Mouse, &img);//마우스 클릭 시 이미지 변형
		}
		else if (key == 'r')
		{
			img = Readimage.clone();
			imshow("picture editor", img);
			return;
		}
		else if (key == 'b')
			exit(0);
	}
	
	return;
}