#include <opencv/cv.h>
#include <opencv/highgui.h>

#define LOW 0
#define HIGH 255
#define HISTOGRAM_SIZE 256

/*
	히스토그램은 시험에도 나오므로 잘 공부해두어야 한다.
*/
int main()
{
	int i, j, value;

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* histogramImage_R = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogramImage_G = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	IplImage* histogramImage_B = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 3);
	
	CvScalar temp;

	double HIST_R[HISTOGRAM_SIZE], HIST_G[HISTOGRAM_SIZE], HIST_B[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX;

	//히스토그램 배열 초기화
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		HIST_R[i] = LOW;
		HIST_G[i] = LOW;
		HIST_B[i] = LOW;
	}

	//빈도수 조사
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			
			HIST_R[(int)temp.val[2]]++;
			HIST_G[(int)temp.val[1]]++;
			HIST_B[(int)temp.val[0]]++;
		}
	}

	//R 히스토그램 그리기
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

	//G 히스토그램 그리기
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

	//B 히스토그램 그리기
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
	
	cvShowImage("input image", inputImage); // 이미지 보이게 하는 함수
	cvShowImage("histoImage_R image", histogramImage_R);
	cvShowImage("histoImage_G image", histogramImage_G);
	cvShowImage("histoImage_B image", histogramImage_B);
	
	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyAllWindows();

	cvReleaseImage(&histogramImage_R);
	cvReleaseImage(&histogramImage_G);
	cvReleaseImage(&histogramImage_B);
	cvReleaseImage(&inputImage); // 이미지 해제

	return 0;
}