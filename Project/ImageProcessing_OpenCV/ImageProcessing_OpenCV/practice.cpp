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
			//�� �̹������� ���� ��ǥ ���� �ҷ���
			inputValue1 = cvGet2D(inputImage1, i, j);
			inputValue2 = cvGet2D(inputImage2, i, j);
			//���� 1/2�� ��
			outputValue.val[0] = inputValue1.val[0] / 2 + inputValue2.val[0] / 2;

			cvSet2D(outputImage, i, j, outputValue);
		}
	}


	cvShowImage("Input Image1", inputImage1);
	cvShowImage("Input Image2", inputImage2);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage1);
	cvReleaseImage(&inputImage2);
	cvReleaseImage(&outputImage);
	
	return 0;
}