#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	int i, j;
	CvScalar inputValue1, inputValue2, outputValue;

	IplImage *inputImage1 = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *inputImage2 = cvLoadImage("Penguin.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize(inputImage1->width, inputImage1->height),8,1);

	for (i = 0; i < inputImage1->height; i++) {
		for (j = 0; j < inputImage1->width; j++) {
			//각 이미지에서 같은 좌표 값을 불러옴
			inputValue1 = cvGet2D(inputImage1, i, j);
			inputValue2 = cvGet2D(inputImage2, i, j);
			//각각 1/2씩 합
			outputValue.val[0] = inputValue1.val[0] / 2 + inputValue2.val[0] / 2;

			cvSet2D(outputImage, i, j, outputValue);
		}
	}


	cvShowImage("Input Image1", inputImage1);
	cvShowImage("Input Image2", inputImage2);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage1);
	cvReleaseImage(&inputImage2);
	cvReleaseImage(&outputImage);
	
	return 0;
}