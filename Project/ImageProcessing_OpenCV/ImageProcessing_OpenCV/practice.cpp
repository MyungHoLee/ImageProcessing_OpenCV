#include <opencv/cv.h>
#include <opencv/highgui.h>

#define ZOOM_RATE 2 // ���� Ȯ�� ����

/*
* ���� ������ �̿� ȭ�� ������
*/

int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* outputImage = cvCreateImage(cvSize(inputImage->width * ZOOM_RATE, inputImage->height * ZOOM_RATE), 8, 1);

	for (i = 0; i < outputImage->height; i++) {
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvGet2D(inputImage, i / ZOOM_RATE, j / ZOOM_RATE));
			// ���� ����ȯ ȭ�� �Է�
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

// ������� ���� �Լ�
IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]) {
	IplImage* tempinputImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), IPL_DEPTH_8U, 1); // ��ǲ �̹������� 2�� ũ�� ����
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), IPL_DEPTH_8U, 1);

	int i, j, n, m;
	double Sum = 0.0;
	CvScalar tempScalar;

	cvSetZero(tempinputImage); // ���ó���� 0 ������ �̿�, temp�̹��� ������ ä��

	for (i = 0; i < inputImage->height; i++) { // temp�̹����� ��ǲ �̹��� ����
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempinputImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i++) // ������� ����
	{
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) { // ����ũ�� �����ϸ鼭 Sum�� ����
					tempScalar = cvGet2D(tempinputImage, i + n, j + m);
					Sum += Mask[n][m] * tempScalar.val[0];
				}
			}
			cvSet2D(outputImage, i, j, cvScalar(Sum)); // ������� �ƿ�ǲ �̹����� ����
			Sum = 0.0;
		}
	}

	cvReleaseImage(&tempinputImage);

	return outputImage;
}