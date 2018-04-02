#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

/*
* ������׷� ��ȭ
*/
void Show_histogram(IplImage* img,const char* imgWindowNmae,const char* histogramWindowName);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* targetImage = cvLoadImage("Jeju.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* specImage = cvCreateImage(cvGetSize(inputImage), inputImage->depth, inputImage->nChannels);

	int i, j, value;
	double in_SUM = 0.0;
	double tar_SUM = 0.0;

	CvScalar temp;

	double inputHist[HISTOGRAM_SIZE];
	int inputEqHist[HISTOGRAM_SIZE];
	double targetHist[HISTOGRAM_SIZE];
	int targetEqHist[HISTOGRAM_SIZE];
	int RevHist[HISTOGRAM_SIZE];

	// �ʱ�ȭ
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		inputHist[i] = LOW;
		targetHist[i] = LOW;
	}

	// ������׷� �����
	// ��ǲ
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			inputHist[value]++;
		}
	}

	// Ÿ��
	for (i = 0; i < targetImage->height; i++) {
		for (j = 0; j < targetImage->width; j++) {
			temp = cvGet2D(targetImage, i, j);
			value = (int)temp.val[0];
			targetHist[value]++;
		}
	}
	

	// ��Ȱȭ
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		in_SUM = in_SUM + inputHist[i];
		inputEqHist[i] = (int)(in_SUM * HIGH / (inputImage->height * inputImage->width));

		tar_SUM = tar_SUM + targetHist[i];
		targetEqHist[i] = (int)(tar_SUM * HIGH / (targetImage->height * targetImage->width));
	}

	// ����Ȱȭ ���̺�
	value = targetEqHist[0];
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			if (i == targetEqHist[j]) {
				value = j;
				break;
			}
		}
		RevHist[i] = value;
	}

	// ��ȭ
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			cvSet2D(specImage, i, j, cvScalar(RevHist[(int)temp.val[0]]));
		}
	}

	Show_histogram(inputImage, "input image", "input histogram");
	Show_histogram(targetImage, "target image", "target histogram");
	Show_histogram(specImage, "spec image", "spec histogram");

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	cvDestroyAllWindows();
	cvReleaseImage(&targetImage); // �̹��� ����
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