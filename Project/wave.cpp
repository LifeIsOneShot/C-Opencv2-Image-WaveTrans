#include "wave.h"
#include "mouse.h"

void showWave(Image image, Mat Readimage, Mat wave, Mat rote, Mat BT) {

	image.rotateWaveTrans(Readimage, rote);		//ȸ��
	namedWindow("ȸ��");
	imshow("ȸ��", rote);
	
	image.waterWaveTrans(Readimage, wave);		//���� �ĵ�
	namedWindow("���� �ĵ�");
	imshow("���� �ĵ�", wave);	
	
	namedWindow("B�� �ĵ�");						//B�� �ĵ�
	imshow("B�� �ĵ�", BT);
	setMouseCallback("B�� �ĵ�",Mouse);//���콺 Ŭ�� �� �̹��� ����

	return;
}