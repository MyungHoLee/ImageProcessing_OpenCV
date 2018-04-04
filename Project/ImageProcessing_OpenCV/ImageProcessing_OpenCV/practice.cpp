#include <opencv/cv.h>
#include <opencv/highgui.h>

/*
	가우시안 필터링 처리
*/
IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* ResultImage_1 = NULL;
	IplImage* ResultImage_2 = NULL;

	double SharpeningMask_1[3][3] = { {-1., -1., -1.}, {-1.,9.,-1.},{-1.,-1.,-1.} };
	double SharpeningMask_2[3][3] = { {0., -1., 0.}, {-1., 5., -1.}, {0., -1., 0.} };

	ResultImage_1 = ConvolutionProcess(inputImage, SharpeningMask_1);
	ResultImage_2 = ConvolutionProcess(inputImage, SharpeningMask_2);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image 1", ResultImage_1);
	cvShowImage("Result Image 2", ResultImage_2);

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	cvDestroyAllWindows();
	cvReleaseImage(&ResultImage_1);
	cvReleaseImage(&ResultImage_2);
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