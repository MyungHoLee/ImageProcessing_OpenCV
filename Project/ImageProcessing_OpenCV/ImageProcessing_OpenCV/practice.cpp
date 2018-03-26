#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

#define ENDIN_LOW 30
#define ENDIN_HIGH 225

/*
* ������׷��� �̿��� ȭ�� ��ó��
*/
void Show_histogram(IplImage* img,const char* imgWindowNmae,const char* histogramWindowName);

int main()
{
	int i, j;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* endin_Image = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	CvScalar temp;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			if (temp.val[0] >= ENDIN_HIGH) {
				cvSet2D(endin_Image, i, j, cvScalar(255));
			}
			else if (temp.val[0] <= ENDIN_LOW) {
				cvSet2D(endin_Image, i, j, cvScalar(0));
			}
			else {
				cvSet2D(endin_Image, i, j, cvScalar((temp.val[0] - ENDIN_LOW) * HIGH / (ENDIN_HIGH - ENDIN_LOW)));
			}
		}
	}

	Show_histogram(inputImage, "input image", "input histogram");
	Show_histogram(endin_Image, "EndIn image", "EndIn histogram");

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	cvDestroyAllWindows();
	cvReleaseImage(&inputImage); // �̹��� ����
	cvReleaseImage(&inputImage);

	return 0;
}

void Show_histogram(IplImage* img,const char* imgWindowName,const char* histogramWindowName)
{
	int i, j, value;
	IplImage* inputImage = img;
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1);

	CvScalar temp;

	double HIST[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX, MIN, DIF;

	// ������׷� �迭 �ʱ�ȭ
	for (i = 0; i < HISTOGRAM_SIZE; i++) HIST[i] = LOW;

	// �󵵼� ����
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	// ����ȭ
	MAX = HIST[0];
	MIN = HIST[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST[i] > MAX) MAX = HIST[i];
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) scale_HIST[i] = (unsigned char)((HIST[i] * HIGH) / MAX);

	cvSet(histogramImage, cvScalar(255));

	//������׷��� ���� ���������� ���
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	//�Ʒ� �κп� ������׷��� ���� ǥ��
	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage, i, j, cvScalar(j));
		}
	}

	cvShowImage(imgWindowName, inputImage);
	cvShowImage(histogramWindowName, histogramImage);

}