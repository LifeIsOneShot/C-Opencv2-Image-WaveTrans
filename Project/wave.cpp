#include "wave.h"
#include "mouse.h"

void showWave(Image image, Mat Readimage, Mat wave, Mat rote, Mat BT) {

	image.rotateWaveTrans(Readimage, rote);		//회전
	namedWindow("회전");
	imshow("회전", rote);
	
	image.waterWaveTrans(Readimage, wave);		//물결 파동
	namedWindow("물결 파동");
	imshow("물결 파동", wave);	
	
	namedWindow("B형 파동");						//B형 파동
	imshow("B형 파동", BT);
	setMouseCallback("B형 파동",Mouse);//마우스 클릭 시 이미지 변형

	return;
}