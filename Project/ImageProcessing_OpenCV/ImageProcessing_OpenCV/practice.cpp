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
	IplImage* sumImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* subImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* mulImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* divImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	
	CvScalar pixelValue, temp;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);
			// 덧셈 연산
			if (pixelValue.val[0] + SUM_CONSTANT >= 255) {
				temp.val[0] = 255;
				cvSet2D(sumImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumImage, i, j, temp);
			}
			// 뺄셈 연산
			if (pixelValue.val[0] - SUB_CONSTANT < 0)
			{
				temp.val[0] = 0;
				cvSet2D(subImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - SUB_CONSTANT;
				cvSet2D(subImage, i, j, temp);
			}
			// 곱셈 연산
			if (pixelValue.val[0] + MUL_CONSTANT >= 0)
			{
				temp.val[0] = 255;
				cvSet2D(mulImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] * MUL_CONSTANT;
				cvSet2D(mulImage, i, j, temp);
			}
			// 나눗셈 연산
			if (pixelValue.val[0] / DIV_CONSTANT < 0)
			{
				temp.val[0] = 0;
				cvSet2D(divImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - DIV_CONSTANT;
				cvSet2D(divImage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("창 이름", 오토사이즈) 창 만드는 함수
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sub image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mul image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("div image", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // 이미지 보이게 하는 함수
	cvShowImage("sum image", sumImage); // 이미지 보이게 하는 함수
	cvShowImage("sub image", subImage);
	cvShowImage("mul image", mulImage);
	cvShowImage("div image", divImage);

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyWindow("input image"); // 창 끄기
	cvDestroyWindow("sum image");
	cvDestroyWindow("sub image");
	cvDestroyWindow("mul image");
	cvDestroyWindow("div image");

	cvReleaseImage(&inputImage); // 이미지 해제
	cvReleaseImage(&sumImage);
	cvReleaseImage(&subImage);
	cvReleaseImage(&mulImage);
	cvReleaseImage(&divImage);

	return 0;
}