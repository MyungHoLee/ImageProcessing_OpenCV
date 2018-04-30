#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	int i, j;
	CvScalar tempValue01, tempValue02, resultValue;
	bool isBackGroung = false;

	CvCapture *capture = cvCreateFileCapture("test.avi");// 동영상 연결
	IplImage *frame;

	IplImage *grayFrame = cvCreateImage(cvSize(320, 240), 8, 1);
	IplImage *backGroundImage = cvCreateImage(cvGetSize(grayFrame), 8, 1);
	IplImage *resultImage = cvCreateImage(cvGetSize(grayFrame), 8, 1);

	while (1) {
		frame = cvQueryFrame(capture); // 동영상의 프레임을 복사
		if (!frame) break;
		cvShowImage("Source", frame);

		cvCvtColor(frame, grayFrame, CV_RGB2GRAY);// 컬러영상을 흑백으로 변환
		cvShowImage("Gray Scale", grayFrame);

		if (isBackGroung != true) {
			cvCopy(grayFrame, backGroundImage); // 배경영상을 추출.
			isBackGroung = true;
		}
		cvShowImage("Back Ground Image", backGroundImage);

		for (i = 0; i < grayFrame->height; i++) {
			for (j = 0; j < grayFrame ->width; j++) {
				tempValue01 = cvGet2D(grayFrame, i, j);
				tempValue02 = cvGet2D(backGroundImage, i, j);
				resultValue.val[0] = abs(tempValue01.val[0] - tempValue02.val[0]);
				cvSet2D(resultImage, i, j, resultValue);
			}
		}
		cvShowImage("Result Image", resultImage);

		if (cvWaitKey(30) == 27) break; // 30ms동안 프로그램 정지. ESC(27)을 누르지 않으면 루프 반복
	}


	cvReleaseCapture(&capture);
	cvDestroyAllWindows();
	cvReleaseImage(&grayFrame);
	cvReleaseImage(&backGroundImage);
	cvReleaseImage(&resultImage);
	
	return 0;
}