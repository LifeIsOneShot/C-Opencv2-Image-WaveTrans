#include "Image.h"

extern Image image;
extern Mat BT;

vector<Point>MouseDown(1), MouseUp(1);

void Mouse(int event, int x, int y, int flags, void *ustc)
{	
	bool flag = false;

	switch (event) {
	case CV_EVENT_LBUTTONDOWN: { //when you press the mouse left botton 
		MouseDown[0]=(Point(x, y));
	}break;

	case CV_EVENT_LBUTTONUP: { //when you release the mouse left botton
	   MouseUp[0]=(Point(x, y));
	   flag = true;
	}break;
	default:
		break;
	}

	if (flag == true){
		image.BTrans(BT, MouseUp, MouseDown);// B형 파동
		imshow("B형 파동", BT);
		flag = false;
	}
}