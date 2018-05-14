#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	int i, j, n, m;
	CvScalar tempValue;

	double filter[3][3] = { {1. / 18., 1. / 18.,1. / 18. },{ 1. / 18., 10. / 18., 1. / 18., },{ 1. / 18., 1. / 18., 1. / 18.} };

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), 8, 1);
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
			tempValue.val[0] = 0.;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue.val[0] += cvGet2D(tempImage, i + n, j + m).val[0] * filter[n][m];
				}
			}
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