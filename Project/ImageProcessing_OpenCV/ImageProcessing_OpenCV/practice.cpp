#include <opencv/cv.h>
#include <opencv/highgui.h>

#define MASKSIZE 3

static int compare(const void *arg1, const void *arg2);

int main()
{
	int i, j, n, m;
	int steps = MASKSIZE - 1;
	CvScalar tempValue;

	//Median Buffer
	double *filter = (double*)malloc(sizeof(double)*MASKSIZE * MASKSIZE);

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + steps, inputImage->height + steps), 8, 1);
	IplImage *outputImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	//Create padding 패딩만들기
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(inputImage, i, j));
		}
	}

	//calculate
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			for (n = 0; n < MASKSIZE; n++) {
				for (m = 0; m < MASKSIZE; m++) {
					filter[n*MASKSIZE + m] = cvGet2D(tempImage, i + n, j + m).val[0];
				}
			}
			qsort(filter, MASKSIZE * MASKSIZE, sizeof(filter[0]), compare);
			tempValue.val[0] = filter[(int)(MASKSIZE *MASKSIZE) / 2];
			cvSet2D(outputImage, i, j, tempValue);
		}
	}

	cvShowImage("input Image", inputImage);
	cvShowImage("Output Image", outputImage);

	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&outputImage);

	return 0;
}

static int compare(const void *arg1, const void *arg2)
{
	if (*(double*)arg1 > *(double*)arg2)
		return 1;
	else if (*(double*)arg1 < *(double*)arg2)
		return -1;
	else
		return 0;

}