#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

bool faceDetection(IplImage * image, CvRect * faceRect) {

	const char * faceClassifier = "haarcascade_frontalface_default.xml";

	CvHaarClassifierCascade * cascade_face = 0;
	cascade_face = (CvHaarClassifierCascade*)cvLoad(faceClassifier, 0, 0, 0);

	if (!cascade_face) {
		printf("error : face cascade error \n");
		return false;
	}

	CvMemStorage * storage_face = 0;
	storage_face = cvCreateMemStorage(0);

	if (!storage_face) {
		printf("error : storage error \n");
		cvReleaseHaarClassifierCascade(&cascade_face);
		return false;
	}

	CvSeq* faces = 0;
	CvRect* tempR = 0;

	faces = cvHaarDetectObjects(image, cascade_face, storage_face, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT);

	if (!faces->total) {
		cvReleaseMemStorage(&storage_face);
		cvReleaseHaarClassifierCascade(&cascade_face);
		return false;
	}

	tempR = (CvRect*)cvGetSeqElem(faces, 0);
	faceRect->x = tempR->x;
	faceRect->y = tempR->y;
	faceRect->height = tempR->height;
	faceRect->width = tempR->width;

	cvReleaseHaarClassifierCascade(&cascade_face);
	cvReleaseMemStorage(&storage_face);

	return true;
}

bool eyeDetection(IplImage * faceImage, CvRect * leftEyeRect, CvRect * rightEyeRect) {

	const char * leftEyeClassifier = "haarcascade_mcs_lefteye.xml";
	const char * rightEyeClassifier = "haarcascade_mcs_righteye.xml";

	CvHaarClassifierCascade * cascade_leftEye = 0;
	cascade_leftEye = (CvHaarClassifierCascade*)cvLoad(leftEyeClassifier, 0, 0, 0);

	CvHaarClassifierCascade * cascade_rightEye = 0;
	cascade_rightEye = (CvHaarClassifierCascade*)cvLoad(rightEyeClassifier, 0, 0, 0);

	if (!cascade_leftEye || !cascade_rightEye) {
		printf("error : face cascade error \n");
		return false;
	}

	CvMemStorage * storage_leftEye = 0;
	storage_leftEye = cvCreateMemStorage(0);

	CvMemStorage * storage_rightEye = 0;
	storage_rightEye = cvCreateMemStorage(0);

	if (!storage_leftEye || !storage_rightEye) {
		printf("error : storage error \n");
		cvReleaseHaarClassifierCascade(&cascade_leftEye);
		cvReleaseHaarClassifierCascade(&cascade_rightEye);
		return false;
	}

	CvSeq* leftEye = 0;
	CvSeq* rightEye = 0;
	CvRect* tempLEye = 0;
	CvRect* tempREye = 0;

	leftEye = cvHaarDetectObjects(faceImage, cascade_leftEye, storage_leftEye, 1.3, 3, CV_HAAR_FIND_BIGGEST_OBJECT);
	rightEye = cvHaarDetectObjects(faceImage, cascade_rightEye, storage_rightEye, 1.3, 3, CV_HAAR_FIND_BIGGEST_OBJECT);

	if (leftEye->total) {
		tempLEye = (CvRect*)cvGetSeqElem(leftEye, 0);
		leftEyeRect->x = tempLEye->x;
		leftEyeRect->y = tempLEye->y;
		leftEyeRect->height = tempLEye->height;
		leftEyeRect->width = tempLEye->width;
	}

	if (rightEye->total) {
		tempREye = (CvRect*)cvGetSeqElem(rightEye, 0);
		rightEyeRect->x = tempREye->x;
		rightEyeRect->y = tempREye->y;
		rightEyeRect->height = tempREye->height;
		rightEyeRect->width = tempREye->width;
	}

	// 검출된 왼쪽 눈들의 좌표를 이용하여 정확한 왼쪽 눈의 좌표를 구할 수 있도록 조건을 설정
	for (int i = 1; i < leftEye->total; i++) {
		tempLEye = (CvRect*)cvGetSeqElem(leftEye, i);
	}

	// 검출된 오른쪽 눈들의 좌표를 이용하여 정확한 오른쪽 눈의 좌표를 구할 수 있도록 조건을 설정
	for (int i = 1; i < rightEye->total; i++) {
		tempREye = (CvRect*)cvGetSeqElem(rightEye, i);
	}

	cvReleaseHaarClassifierCascade(&cascade_leftEye);
	cvReleaseHaarClassifierCascade(&cascade_rightEye);
	cvReleaseMemStorage(&storage_leftEye);
	cvReleaseMemStorage(&storage_rightEye);

	return true;
}

int main()
{
	CvRect faceRect = { 0,0,0,0 }, leftEyeRect = { 0,0,0,0 }, rightEyeRect = { 0, 0, 0, 0 };
	IplImage* img = cvLoadImage("원빈.jpg", 1);
	
	cvWaitKey();
	faceDetection(img, &faceRect);
	cvRectangle(img,
		cvPoint(faceRect.x, faceRect.y),
		cvPoint(faceRect.x + faceRect.width, faceRect.y + faceRect.height),
		cvScalar(0, 255, 0), 3, CV_AA, 0);

	eyeDetection(img, &leftEyeRect, &rightEyeRect);

	//검출한 왼쪽 눈을 빨간색 사각형 영역으로 표현
	cvRectangle(img,
		cvPoint(leftEyeRect.x, leftEyeRect.y),
		cvPoint(leftEyeRect.x + leftEyeRect.width, leftEyeRect.y + leftEyeRect.height),
		cvScalar(0, 0, 255), 3, CV_AA, 0);

	// 검출한 오른쪽 눈을 파란색 사각형 영역으로 표현
	cvRectangle(img,
		cvPoint(rightEyeRect.x, rightEyeRect.y),
		cvPoint(rightEyeRect.x + rightEyeRect.width, rightEyeRect.y + rightEyeRect.height),
		cvScalar(255, 0, 0), 3, CV_AA, 0);

	cvShowImage("Detection Result", img);
	cvWaitKey();
	cvDestroyAllWindows();
	cvReleaseImage(&img);

	return 0;
}
