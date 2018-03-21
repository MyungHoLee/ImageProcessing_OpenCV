#include <opencv/cv.h>
#include <opencv/highgui.h>

#define BINARY_THRESHOLD 130

/*
	화소 점 처리
	이진화
*/
int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	
	CvScalar pixelValue, temp;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);

			if (pixelValue.val[0] >= BINARY_THRESHOLD) {
				temp.val[0] = 255;
				cvSet2D(outputImage, i, j, temp);
			}
			else {
				temp.val[0] = 0;
				cvSet2D(outputImage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("창 이름", 오토사이즈) 창 만드는 함수
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // 이미지 보이게 하는 함수
	cvShowImage("output image", outputImage);
	
	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyWindow("input image"); // 창 끄기
	cvDestroyWindow("output image");
	
	cvReleaseImage(&inputImage); // 이미지 해제
	cvReleaseImage(&outputImage);
	
	return 0;
}