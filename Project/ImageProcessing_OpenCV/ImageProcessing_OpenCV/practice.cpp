#include <opencv/cv.h>
#include <opencv/highgui.h>

#define SUB_SAMPLING_RATE 2 // ��� ����

void Swap(double *a, double *b); // ������ ��ȯ
void BubbleSort(double *A, int MAX); // ������ ����
/*
* �缱�� ȭ�� ������
*/

int main()
{
	int i, j, n, m, k, index = 0;
	double *Mask, *OutputValue;
	CvScalar tempScalar;

	Mask = new double[SUB_SAMPLING_RATE * SUB_SAMPLING_RATE]; // ����ũ ũ��

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *outputImage = cvCreateImage(cvSize((inputImage->width + 1)/ SUB_SAMPLING_RATE, (inputImage->height
		+1) / SUB_SAMPLING_RATE), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 1, inputImage->height + 1), 8, 1);

	OutputValue = new double[(inputImage->width + 1) / SUB_SAMPLING_RATE * (inputImage->height + 1) / SUB_SAMPLING_RATE];
	
	cvSetZero(tempImage);

	for (i = 0; i < inputImage->height; i++) { // ��ǲ�̹��� temp�� �ű�
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempImage, i, j, cvGet2D(inputImage, i, j));
		}
	}

	for (i = 0; i < inputImage->height; i = i + SUB_SAMPLING_RATE) {
		for (j = 0; j < inputImage->width; j = j + SUB_SAMPLING_RATE) {
			for (n = 0; n < SUB_SAMPLING_RATE; n++) {
				for (m = 0; m < SUB_SAMPLING_RATE; m++) {
					tempScalar = cvGet2D(tempImage, i + n, j + m);
					Mask[n*SUB_SAMPLING_RATE + m] = tempScalar.val[0]; // ����ũ ������ ȭ�Ұ��� �迭�� ����
				}
			}
			BubbleSort(Mask, SUB_SAMPLING_RATE * SUB_SAMPLING_RATE); // ����ũ �迭 ���� ����
			OutputValue[index++] = Mask[(int)(SUB_SAMPLING_RATE * SUB_SAMPLING_RATE / 2)]; // OutputValue ��Ŀ� �߰����� ���
		}
	}

	for (i = 0; i < outputImage->height; i++) { //OutputValue ��� ���� outputImage�� �Է�
		for (j = 0; j < outputImage->width; j++) {
			cvSet2D(outputImage, i, j, cvScalar(OutputValue[i*outputImage->width + j]));
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);

	cvWaitKey(); // �� �Լ��� �ȳ����� �̹����� �ҷ������ٰ� �ٷ� ����(��ȣ �ȿ� Ư���� Ű�� ������ �� Ű�� ������ �� ����, ��������� �ƹ�Ű�� ������ �� ������.)
	
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
