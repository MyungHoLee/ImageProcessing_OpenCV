#include <opencv/cv.h>
#include <opencv/highgui.h>

#define SUB_SAMPLING_RATE 2 // 축소 비율

void Swap(double *a, double *b); // 데이터 교환
void BubbleSort(double *A, int MAX); // 데이터 정렬
/*
* 양선형 화소 보간법
*/

int main()
{
	int i, j, n, m, k, index = 0;
	double *Mask, *OutputValue;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE]; // 마스크 크기

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize((inputImage->width + 1)/ SUB_SAMPLING_RATE, (inputImage->height
		+1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 1, inputImage->height + 1), 8, 1);

	OutputValue = new double[(inputImage->width + 1) / SUB_SAMPLING_RATE * (inputImage->height + 1) / SUB_SAMPLING_RATE];
	
	cvSetZero(tempImage);

	for (i = 0; i < inputImage->height; i++) { // 인풋이미지 temp에 옮김
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempImage, i, j, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j < inputImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n < SUB_SAMPLING_RATE; n++) {
				for (m = 0; m < SUB_SAMPLING_RATE; m++) {
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0]; // 마스크 범위의 화소값들 배열을 만듬
				}
			}
			BubbleSort(Mask, SUB_SAMPLING_RATE * SUB_SAMPLING_RATE); // 마스크 배열 값들 정렬
			OutputValue[index++] = Mask[(int)(SUB_SAMPLING_RATE * SUB_SAMPLING_RATE / 2)]; // OutputValue 행렬에 중간값들 행렬
		}
	}

	for (i = 0; i < outputImage->height; i++) { //OutputValue 행렬 값들 outputImage에 입력
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // 이 함수를 안넣으면 이미지가 불러와졌다가 바로 꺼짐(괄호 안에 특수한 키를 넣으면 그 키를 눌렀을 때 꺼짐, 비어있으면 아무키나 눌렀을 때 꺼진다.)
	
	cvDestroyAllWindows();
	cvReleaseImage(&outputImage);
	cvReleaseImage(&inputImage);

	return 0;
}

void Swap(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(double *A, int MAX)
{
	int i, j;

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				Swap(&A[j], &A[j + 1]);
			}
		}
	}
}
