#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	IplImage* image = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�

	cvNamedWindow("Test Viewer", CV_WINDOW_AUTOSIZE); // cvNamedWindow("â �̸�", ���������) â ����� �Լ�
	cvShowImage("Test Viewer", image); // �̹��� ���̰� �ϴ� �Լ�

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	cvDestroyWindow("Test Viewer"); // â ����

	cvReleaseImage(&image); // �̹��� ����


	return 0;
}