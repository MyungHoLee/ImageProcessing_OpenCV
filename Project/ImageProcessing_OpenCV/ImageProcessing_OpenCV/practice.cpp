#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#define SUM_CONSTANT 50
#define SUB_CONSTANT 50
#define MUL_CONSTANT 5
#define DIV_CONSTANT 5

/*
	ȭ�� �� ó��
	���� ���� ó��
*/
int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
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

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("â �̸�", ���������) â ����� �Լ�
	cvNamedWindow("And", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Or", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Xor", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // �̹��� ���̰� �ϴ� �Լ�
	cvShowImage("And", andImage);
	cvShowImage("Or", orImage);
	cvShowImage("Xor", xorImage);
	
	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyWindow("input image"); // â ����
	cvDestroyWindow("And");
	cvDestroyWindow("Or");
	cvDestroyWindow("Xor");
	
	cvReleaseImage(&inputImage); // �̹��� ����
	cvReleaseImage(&mask);
	cvReleaseImage(&andImage);
	cvReleaseImage(&orImage);
	cvReleaseImage(&xorImage);

	return 0;
}