#include <opencv/cv.h>
#include <opencv/highgui.h>

/*
* ���� ó��
*/
IplImage* ConvolutionProcess(IplImage* inputImage, double Mask[3][3]);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* ResultImage = NULL;

	double BlurringMask[3][3] = { {1 / 9.,1 / 9., 1 / 9.},{ 1 / 9.,1 / 9., 1 / 9.},{ 1 / 9.,1 / 9., 1 / 9. } };

	ResultImage = ConvolutionProcess(inputImage, BlurringMask);

	cvShowImage("input Image", inputImage);
	cvShowImage("Result Image", ResultImage);

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	cvDestroyAllWindows();
	cvReleaseImage(&ResultImage);
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