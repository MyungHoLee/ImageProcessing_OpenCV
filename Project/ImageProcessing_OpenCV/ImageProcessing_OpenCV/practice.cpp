#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ZOOM_RATE 2 // 영상 확대 비율

/*
* 가장 인접한 이웃 화소 보간법
*/

int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width * ZOOM_RATE, inputImage->height * ZOOM_RATE), 8, 1);

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvGet2D(inputImage, i / ZOOM_RATE, j / ZOOM_RATE));
			// 가장 인접환 화소 입력
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

// 컨볼루션 연산 함수
IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1); // 인풋 이미지보다 2씩 크게 선언
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // 경계처리는 0 삽입을 이용, temp이미지 검은색 채움

	for (i = 0; i < inputImage->height; i++) { // temp이미지에 인풋 이미지 복사
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) // 컨벌루션 연산
	{
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // 마스크와 연산하면서 Sum에 누적
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // 결과값을 아웃풋 이미지에 넣음
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}