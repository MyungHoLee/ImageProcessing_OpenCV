#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

/*
	������׷��� ���迡�� �����Ƿ� �� �����صξ�� �Ѵ�.
*/
int main()
{
	int i, j, value;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // cvLoadImage("�ּ�", �÷��� �ε�): �̹��� �ҷ����� �Լ�
	IplImage* histogramImage_R = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogramImage_G = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogramImage_B = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	
	CvScalar temp;

	double HIST_R[HISTOGRAM_SIZE], HIST_G[HISTOGRAM_SIZE], HIST_B[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX;

	//������׷� �迭 �ʱ�ȭ
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		HIST_R[i] = LOW;
		HIST_G[i] = LOW;
		HIST_B[i] = LOW;
	}

	//�󵵼� ����
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			
			HIST_R[(int)temp.val[2]]++;
			HIST_G[(int)temp.val[1]]++;
			HIST_B[(int)temp.val[0]]++;
		}
	}

	//R ������׷� �׸���
	MAX = HIST_R[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_R[i] > MAX)
			MAX = HIST_R[i];
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_R[i] * HIGH) / MAX);
	}

	cvSet(histogramImage_R, cvScalar(255, 255, 255));

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage_R, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage_R, i, j, cvScalar(0, 0, j));
		}
	}

	//G ������׷� �׸���
	MAX = HIST_G[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_G[i] > MAX)
			MAX = HIST_G[i];
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_G[i] * HIGH) / MAX);
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_G[i] * HIGH) / MAX);
	}
	cvSet(histogramImage_G, cvScalar(255, 255, 255));

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage_G, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage_G, i, j, cvScalar(0, j, 0));
		}
	}

	//B ������׷� �׸���
	MAX = HIST_B[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST_B[i] > MAX)
			MAX = HIST_B[i];
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST_B[i] * HIGH) / MAX);
	}
	cvSet(histogramImage_B, cvScalar(255, 255, 255));

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage_B, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage_B, i, j, cvScalar(j, 0, 0));
		}
	}
	
	cvShowImage("input image", inputImage); // �̹��� ���̰� �ϴ� �Լ�
	cvShowImage("histoImage_R image", histogramImage_R);
	cvShowImage("histoImage_G image", histogramImage_G);
	cvShowImage("histoImage_B image", histogramImage_B);
	
	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
	cvDestroyAllWindows();

	cvReleaseImage(&histogramImage_R);
	cvReleaseImage(&histogramImage_G);
	cvReleaseImage(&histogramImage_B);
	cvReleaseImage(&inputImage); // �̹��� ����

	return 0;
}