#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define SUM_CONSTANT 50
#define SUB_CONSTANT 50
#define MUL_CONSTANT 5
#define DIV_CONSTANT 5

/*
	화소 점 처리
	덧셈 연산 처리
*/
int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* mask = cvLoadImage("mask.png", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* andImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* orImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* xorImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	CvScalar pixelValue;

	unsigned char temp1, temp2;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);
			temp1 = (unsigned char)pixelValue.val[0];

			pixelValue = cvGet2D(mask, i, j);
			temp2 = (unsigned char)pixelValue.val[0];

			pixelValue.val[0] = (double)(temp1 & temp2);
			cvSet2D(andImage, i, j, pixelValue);

			pixelValue.val[0] = (double)(temp1 | temp2);
			cvSet2D(orImage, i, j, pixelValue);

			pixelValue.val[0] = (double)(temp1 ^ temp2);
			cvSet2D(xorImage, i, j, pixelValue);
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("창 이름", 오토사이즈) 창 만드는 함수
	cvNamedWindow("And", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Or", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Xor", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // 이미지 보이게 하는 함수
	cvShowImage("And", andImage);
	cvShowImage("Or", orImage);
	cvShowImage("Xor", xorImage);
	
	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyWindow("input image"); // 창 끄기
	cvDestroyWindow("And");
	cvDestroyWindow("Or");
	cvDestroyWindow("Xor");
	
	cvReleaseImage(&inputImage); // 이미지 해제
	cvReleaseImage(&mask);
	cvReleaseImage(&andImage);
	cvReleaseImage(&orImage);
	cvReleaseImage(&xorImage);

	return 0;
}