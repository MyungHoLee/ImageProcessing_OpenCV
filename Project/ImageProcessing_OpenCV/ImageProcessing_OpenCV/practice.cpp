#include <opencv/cv.h>
#include <opencv/highgui.h>

#define THRESHOLD 130

int main()
{
	int i, j, n, m, Dilation_Sum = 0, Erosion_Sum = 0;
	CvScalar tempValue;
	//침식마스크
	double Erosion_Mask[3][3] = { {255.,255., 255.},{ 255., 255., 255.}, { 255., 255., 255.} };
	//팽창 마스크
	double Dilation_Mask[3][3] = { {0.,0., 0.}, { 0., 0., 0.}, { 0., 0., 0.} };

	IplImage *inputImage = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage *binaryImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *tempImage = cvCreateImage(cvSize(inputImage->width + 2, inputImage->height + 2), 8, 1);
	IplImage *ErosionImage = cvCreateImage(cvGetSize(inputImage), 8, 1);
	IplImage *DilationImage = cvCreateImage(cvGetSize(inputImage), 8, 1);

	//이진화
	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			tempValue = cvGet2D(inputImage, i, j);
			if (tempValue.val[0] > THRESHOLD)
				cvSet2D(binaryImage, i, j, cvScalar(255));
			else
				cvSet2D(binaryImage, i, j, cvScalar(0));
		}
	}

	//패딩만들기
	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			cvSet2D(tempImage, i + 1, j + 1, cvGet2D(binaryImage, i, j));
		}
	}

	//연산
	for (i = 0; i < binaryImage->height; i++) {
		for (j = 0; j < binaryImage->width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					tempValue = cvGet2D(tempImage, i + n, j + m);
					if (Erosion_Mask[n][m] == tempValue.val[0])
						Erosion_Sum += 1;
					if (Dilation_Mask[n][m] == tempValue.val[0])
						Dilation_Sum += 1;
				}
			}
			if (Erosion_Sum == 9)
				cvSet2D(ErosionImage, i, j, cvScalar(255));
			else
				cvSet2D(ErosionImage, i, j, cvScalar(0));

			if (Dilation_Sum == 9)
				cvSet2D(DilationImage, i, j, cvScalar(0));
			else
				cvSet2D(DilationImage, i, j, cvScalar(255));

			Erosion_Sum = 0;
			Dilation_Sum = 0;
		}
	}

	cvShowImage("Binary Image", binaryImage);
	cvShowImage("Erosion Image", ErosionImage);
	cvShowImage("Dilation Image", DilationImage);
	cvWaitKey();

	cvDestroyAllWindows();
	cvReleaseImage(&binaryImage);
	cvReleaseImage(&ErosionImage);
	cvReleaseImage(&DilationImage);

	return 0;
}