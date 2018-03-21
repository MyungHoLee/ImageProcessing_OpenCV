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

	IplImage* inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE); // cvLoadImage("주소", 컬러로 로드): 이미지 불러오는 함수
	IplImage* histogramImage = cvCreateImage(cvSize(HISTOGRAM_SIZE, HISTOGRAM_SIZE + 20), IPL_DEPTH_8U, 1);
	
	CvScalar temp;

	double HIST[HISTOGRAM_SIZE];
	unsigned char scale_HIST[HISTOGRAM_SIZE];
	double MAX;

	//히스토그램 배열 초기화
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		HIST[i] = LOW;
	}

	//빈도수 조사
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			temp = cvGet2D(inputImage, i, j);
			value = (int)temp.val[0];
			HIST[value]++;
		}
	}

	//정규화를 위한 최대값 구하기
	MAX = HIST[0];

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		if (HIST[i] > MAX)
			MAX = HIST[i];
	}

	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		scale_HIST[i] = (unsigned char)((HIST[i] * HIGH) / MAX);
	}
	cvSet(histogramImage, cvScalar(255));

	//히스토그램의 값은 검은색으로 출력
	for (i = 0; i < HISTOGRAM_SIZE; i++) {
		for (j = 0; j < scale_HIST[i]; j++) {
			cvSet2D(histogramImage, HISTOGRAM_SIZE - j - 1, i, cvScalar(0));
		}
	}

	for (i = HISTOGRAM_SIZE + 5; i < HISTOGRAM_SIZE + 20; i++) {
		for (j = 0; j < HISTOGRAM_SIZE; j++) {
			cvSet2D(histogramImage, i, j, cvScalar(j));
		}
	}

	//cvNamedWindow("input image", CV_WINDOW_AUTOSIZE); // cvNamedWindow("창 이름", 오토사이즈) 창 만드는 함수
	//cvNamedWindow("output image", CV_WINDOW_AUTOSIZE);
	
	cvShowImage("input image", inputImage); // 이미지 보이게 하는 함수
	cvShowImage("output image", histogramImage);
	
	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyAllWindows();

	cvReleaseImage(&inputImage); // 이미지 해제
	cvReleaseImage(&inputImage);
	
	return 0;
}