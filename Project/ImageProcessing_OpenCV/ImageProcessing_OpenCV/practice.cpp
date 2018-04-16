#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 45 // 회전 각

/*
* 회전
*/

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height),
		inputImage->depth, inputImage->nChannels);

	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree 값을 radian으로 변경

	cosR = cos(Radian);
	sinR = sin(Radian);

	//영상의 중심좌표
	Center_y = inputImage->height / 2;
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			//회전 변환 행렬을 이용하여 새 좌표값 계산
			source_x = (int)((j - Center_x)*cosR + (i - Center_y)*sinR + Center_x);
			source_y = (int)(-(j - Center_x)*sinR + (i - Center_y)*cosR + Center_y);

			//좌표가 영상범위 넘어갔을때 0 처리
			if (source_x < 0 || source_y < 0 || source_y >= inputImage->height || source_x >= inputImage->width)
				Value.val[0] = 0;
			else
				Value = cvGet2D(inputImage, source_y, source_x);
			cvSet2D(outputImage, i, j, Value);
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyAllWindows();
	cvReleaseImage(&outputImage);
	cvReleaseImage(&inputImage);

	return 0;
}