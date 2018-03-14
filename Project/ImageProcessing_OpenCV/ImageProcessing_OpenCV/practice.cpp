#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	IplImage* image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수

	cvNamedWindow("Test Viewer", CV_WINDOW_AUTOSIZE); // cvNamedWindow("창 이름", 오토사이즈) 창 만드는 함수
	cvShowImage("Test Viewer", image); // 이미지 보이게 하는 함수

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	cvDestroyWindow("Test Viewer"); // 창 끄기

	cvReleaseImage(&image); // 이미지 해제


	return 0;
}