#include <opencv/cv.h>
#include <opencv/highgui.h>

#define PI 3.141592
#define DEGREE 300 // ȸ�� ��

/*
* ȸ��
*/

int main()
{
	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage;

	int i, j, in_Center_y, in_Center_x, source_y, source_x, out_w, out_h, out_Center_y, out_Center_x;
	double Radian, cosR, sinR, Radian90;
	CvScalar Value;

	Radian = (double)DEGREE * PI / 180.0; // degree ���� radian���� ����
	Radian90 = (double)90 * PI / 180.0;
	//Out put Image size
	out_w = abs(inputImage->height * cos(Radian90 - Radian)) + abs(inputImage->width * cos(Radian));
	out_h = abs(inputImage->height * cos(Radian)) + abs(inputImage->width * cos(Radian90 - Radian));

	outputImage = cvCreateImage(cvSize(out_w, out_h), inputImage->depth, inputImage->nChannels);

	cosR = cos(Radian);
	sinR = sin(Radian);

	//������ �߽���ǥ
	out_Center_y = out_h / 2;
	out_Center_x = out_w / 2;
	in_Center_y = inputImage->height / 2;
	in_Center_x = inputImage->width / 2;

	for (i = 0; i < out_h; i++) {
		for (j = 0; j < out_w; j++) {
			source_x = (int)((j - out_Center_x)*cosR + (i - out_Center_y)*sinR + in_Center_x);
			source_y = (int)(-(j - out_Center_x)*sinR + (i - out_Center_y)*cosR + in_Center_y);
			
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