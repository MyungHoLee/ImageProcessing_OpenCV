#include <opencv/cv.h>
#include <opencv/highgui.h>

#define H_POS 30
#define W_POS 130

/*
* �̵�
*/

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height), inputImage->depth, inputImage->nChannels);

	int i, j;

	cvSetZero(outputImage);

	for (i = 0; i < inputImage->height - H_POS; i++) {
		for (j = 0; j < inputImage->width - W_POS; j++) {
			cvSet2D(outputImage, i + H_POS, j + W_POS, cvGet2D(inputImage, i, j));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyAllWindows();
	cvReleaseImage(&outputImage);
	cvReleaseImage(&inputImage);

	return 0;
}