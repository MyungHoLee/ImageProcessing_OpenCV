#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 300 // 회전 각

/*
* 회전
*/

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage;

	int i, j, in_Center_y, in_Center_x, source_y, source_x, out_w, out_h, out_Center_y, out_Center_x;
	double Radian, cosR, sinR, Radian90;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree 값을 radian으로 변경
	Radian90 = (double)90 * PI / 180.0;
	//Out put Image size
	out_w = abs(inputImage->height * cos(Radian90 - Radian)) + abs(inputImage->width * cos(Radian));
	out_h = abs(inputImage->height * cos(Radian)) + abs(inputImage->width * cos(Radian90 - Radian));

	outputImage = cvCreateImage(cvSize(out_w, out_h), inputImage->depth, inputImage->nChannels);

	cosR = cos(Radian);
	sinR = sin(Radian);

	//영상의 중심좌표
	out_Center_y = out_h / 2;
	out_Center_x = out_w / 2;
	in_Center_y = inputImage->height / 2;
	in_Center_x = inputImage->width / 2;

	for (i = 0; i < out_h; i++) {
		for (j = 0; j < out_w; j++) {
			source_x = (int)((j - out_Center_x)*cosR + (i - out_Center_y)*sinR + in_Center_x);
			source_y = (int)(-(j - out_Center_x)*sinR + (i - out_Center_y)*cosR + in_Center_y);
			
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