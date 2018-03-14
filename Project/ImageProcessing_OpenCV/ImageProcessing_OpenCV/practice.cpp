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
	IplImage* sumImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* subImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* mulImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	IplImage* divImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);
	
	CvScalar pixelValue, temp;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			pixelValue = cvGet2D(inputImage, i, j);
			// ���� ����
			if (pixelValue.val[0] + SUM_CONSTANT >= 255) {
				temp.val[0] = 255;
				cvSet2D(sumImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] + SUM_CONSTANT;
				cvSet2D(sumImage, i, j, temp);
			}
			// ���� ����
			if (pixelValue.val[0] - SUB_CONSTANT < 0)
			{
				temp.val[0] = 0;
				cvSet2D(subImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - SUB_CONSTANT;
				cvSet2D(subImage, i, j, temp);
			}
			// ���� ����
			if (pixelValue.val[0] + MUL_CONSTANT >= 0)
			{
				temp.val[0] = 255;
				cvSet2D(mulImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] * MUL_CONSTANT;
				cvSet2D(mulImage, i, j, temp);
			}
			// ������ ����
			if (pixelValue.val[0] / DIV_CONSTANT < 0)
			{
				temp.val[0] = 0;
				cvSet2D(divImage, i, j, temp);
			}
			else {
				temp.val[0] = pixelValue.val[0] - DIV_CONSTANT;
				cvSet2D(divImage, i, j, temp);
			}
		}
	}

	cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("â �̸�", ���������) â ����� �Լ�
	cvNamedWindow("sum image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sub image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mul image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("div image", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // �̹��� ���̰� �ϴ� �Լ�
	cvShowImage("sum image", sumImage); // �̹��� ���̰� �ϴ� �Լ�
	cvShowImage("sub image", subImage);
	cvShowImage("mul image", mulImage);
	cvShowImage("div image", divImage);

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyWindow("input image"); // â ����
	cvDestroyWindow("sum image");
	cvDestroyWindow("sub image");
	cvDestroyWindow("mul image");
	cvDestroyWindow("div image");

	cvReleaseImage(&inputImage); // �̹��� ����
	cvReleaseImage(&sumImage);
	cvReleaseImage(&subImage);
	cvReleaseImage(&mulImage);
	cvReleaseImage(&divImage);

	return 0;
}