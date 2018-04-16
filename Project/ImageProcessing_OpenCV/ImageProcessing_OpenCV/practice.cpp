#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 45 // ȸ�� ��

/*
* ȸ��
*/

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize(inputImage->width, inputImage->height),
		inputImage->depth, inputImage->nChannels);

	int i, j, Center_y, Center_x, source_y, source_x;
	double Radian, cosR, sinR;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree ���� radian���� ����

	cosR = cos(Radian);
	sinR = sin(Radian);

	//������ �߽���ǥ
	Center_y = inputImage->height / 2;
	Center_x = inputImage->width / 2;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			//ȸ�� ��ȯ ����� �̿��Ͽ� �� ��ǥ�� ���
			source_x = (int)((j - Center_x)*cosR + (i - Center_y)*sinR + Center_x);
			source_y = (int)(-(j - Center_x)*sinR + (i - Center_y)*cosR + Center_y);

			//��ǥ�� ������� �Ѿ���� 0 ó��
			if (source_x < 0 || source_y < 0 || source_y >= inputImage->height || source_x >= inputImage->width)
				Value.val[0] = 0;
			else
				Value = cvGet2D(inputImage, source_y, source_x);
			cvSet2D(outputImage, i, j, Value);
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