#include <opencv/cv.h>
#include <opencv/highgui.h>

#define GAMMA_CONSTANT 0.85

/*
	ȭ�� �� ó��
	���� ����
*/
int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* outputImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	
	CvScalar pixelValue, temp;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);

			temp.val[0] = pow(pixelValue.val[0], 1 / GAMMA_CONSTANT);
			if (temp.val[0] < 0) {
				temp.val[0] = 0;
				cvSet2D(outputImage, i, j, temp);
			}
			else if (temp.val[0] > 255) {
				temp.val[0] = 255;
				cvSet2D(outputImage, i, j, temp);
			}
			else {
				cvSet2D(outputImage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("â �̸�", ���������) â ����� �Լ�
	cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // �̹��� ���̰� �ϴ� �Լ�
	cvShowImage("output image", outputImage);
	
	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyWindow("input image"); // â ����
	cvDestroyWindow("output image");
	
	cvReleaseImage(&inputImage); // �̹��� ����
	cvReleaseImage(&outputImage);
	
	return 0;
}