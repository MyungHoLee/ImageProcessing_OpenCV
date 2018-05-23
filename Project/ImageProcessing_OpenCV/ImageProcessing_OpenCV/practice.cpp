#include <opencv/cv.h>
#include <opencv/highgui.h>

struct Complex {
	double Re; //Variables for real numbers 실수부
	double Im; //Variables for imaginary numbers 허수부
};

Complex **FFT; //Pointer to save FFT result

IplImage* FFT2d(IplImage* inpuImage);
void FFT1d(Complex *X, int N, int Log2N);
void Scrambling(Complex *X, int N, int Log2N);
void Butterfly(Complex *X, int N, int Log2N, int mode);
int InverseBitOrder(int index, int Log2N);
void OnSNR(IplImage * inputImage, IplImage * outputImage);

IplImage* IFFT2d(IplImage* FFTSpectrum);
void IFFT1d(Complex *X, int N, int Log2N);

int main()
{
	IplImage* inputImage = cvLoadImage("lena.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* FFTSpectrum;
	IplImage* IFFTImage;

	FFTSpectrum = FFT2d(inputImage); //Fast Fourier Transform
	IFFTImage = IFFT2d(FFTSpectrum); // Reverse 역방향 FFT
	OnSNR(inputImage, IFFTImage);

	cvShowImage("Input Image", inputImage);
	cvShowImage("FFT Spectrum", FFTSpectrum);
	cvShowImage("RFFT Image", IFFTImage);

	cvWaitKey();
	cvReleaseImage(&inputImage);
	cvReleaseImage(&FFTSpectrum);
	cvReleaseImage(&IFFTImage);

	return 0;
}

IplImage* FFT2d(IplImage* inputImage)
{
	int i, j, row, col, Log2N, Num;
	Complex * Data;

	unsigned char **temp;
	double Value, Absol;

	CvScalar tempScalar;

	IplImage* FFTSpectrum = cvCreateImage(cvGetSize(inputImage), 8, 1);

	Num = inputImage->width;
	Log2N = 0;

	while (Num >= 2) //image Width calculation  영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	IplImage* tempImage = cvCreateImage(cvGetSize(inputImage), 8, 1); //Assign storage location

	Data = new Complex[inputImage->width];

	FFT = new Complex *[inputImage->height];
	//Arrangement for storing frequency-domain transformed images
	//주파수 영역 변환 영상을 저장하기 위한 배열
	temp = new unsigned char *[inputImage->height];

	for (i = 0; i < inputImage->height; i++) {
		FFT[i] = new Complex[inputImage->width];
		temp[i] = new unsigned char[inputImage->width];
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++)
		{
			Data[j].Re = (double)inputImage->imageData[i*inputImage->widthStep + j];
			// copy one row of input, the real component value is the value of the image
			//입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; //The complex component value is 0 복소 성분 값은 0
		}
		FFT1d(Data, inputImage->width, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j < inputImage->width; j++) { //Save Results
			FFT[i][j].Re = Data[j].Re;
			FFT[i][j].Im = Data[j].Im;
		}
	}

	Num = inputImage->height;
	Log2N = 0;

	while (Num >= 2) //Image height calculation 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[inputImage->height];

	for (i = 0; i < inputImage->width; i++) {
		for (j = 0; j < inputImage->height; j++) {
			Data[j].Re = FFT[j][i].Re; //Copy a row of images 영상의 한 열을 복사
			Data[j].Im = FFT[j][i].Im;
		}

		FFT1d(Data, inputImage->height, Log2N); //1D FFT 1차원 FFT

		for (j = 0; j < inputImage->height; j++) { //Save Results
			FFT[j][i].Re = Data[j].Re;
			FFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			Value = sqrt((FFT[i][j].Re * FFT[i][j].Re) + (FFT[i][j].Im * FFT[i][j].Im));
			Absol = 20 * log(Value);

			if (Absol > 225.0)
				Absol = 225.0;
			if (Absol < 0.0)
				Absol = 0.0;

			cvSet2D(tempImage, i, j, cvScalar(Absol));
		}
	}
	//shuffling process 셔플링 과정
	for (i = 0; i < inputImage->height; i += inputImage->height / 2) {
		for (j = 0; j < inputImage->width; j += inputImage->width / 2) {
			for (row = 0; row < inputImage->height / 2; row++) {
				for (col = 0; col < inputImage->width / 2; col++) {
					tempScalar = cvGet2D(tempImage, i + row, j + col);
					temp[(inputImage->height / 2 - 1) - row + i][(inputImage->width / 2 - 1) - col + j] = (unsigned char)tempScalar.val[0];
				}
			}
		}
	}

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			cvSet2D(FFTSpectrum, i, j, cvScalar(temp[i][j]));
		}
	}

	delete[] Data, **temp;
	cvReleaseImage(&tempImage);

	return FFTSpectrum;
}

void FFT1d(Complex *X, int N, int Log2N)
{
	Scrambling(X, N, Log2N);
	Butterfly(X, N, Log2N, 1);
}

void Scrambling(Complex *X, int N, int Log2N)
{
	int i;
	Complex *temp;

	temp = new Complex[N];

	for (i = 0; i < N; i++) {
		temp[i].Re = X[InverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[InverseBitOrder(i, Log2N)].Im;
	}

	for (i = 0; i < N; i++) {
		X[i].Re = temp[i].Re;
		X[i].Im = temp[i].Im;
	}

	delete[] temp;
}

void Butterfly(Complex *X, int N, int Log2N, int mode)
{
	int i, j, k, m;
	int start;
	double Value;
	double PI = 3.14159265358979;

	Complex *Y, temp;

	Y = new Complex[N / 2];

	for (i = 0; i < Log2N; i++) {
		Value = pow(2., i + 1);

		if (mode == 1) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j * 2.0 * PI / Value);
				Y[j].Im = -sin(j * 2.0 * PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}

		start = 0;

		for (k = 0; k < N / (int)Value; k++) {
			for (j = start; j < start + (int)(Value / 2); j++) {
				m = j + (int)(Value / 2);
				temp.Re = Y[j - start].Re * X[m].Re - Y[j - start].Im * X[m].Im;
				temp.Im = Y[j - start].Im * X[m].Re + Y[j - start].Re * X[m].Im;

				X[m].Re = X[j].Re - temp.Re;
				X[m].Im = X[j].Im - temp.Im;

				X[j].Re = X[j].Re + temp.Re;
				X[j].Im = X[j].Im + temp.Im;
			}
			start = start + (int)Value;
		}
	}
	if (mode == 2) {
		for (i = 0; i < N; i++) {
			X[i].Re = X[i].Re / N;
			X[i].Im = X[i].Im / N;
		}
	}

	delete[] Y;
}

int InverseBitOrder(int index, int Log2N)
{
	int i, X, Y;

	Y = 0;

	for (i = 0; i < Log2N; i++) {
		X = (index & (1 << i)) >> i;
		Y = (Y << 1) | X;
	}
	return Y;
}


IplImage* IFFT2d(IplImage* FFTSpectrum)
{
	Complex **IFFT;

	int i, j, Num, Log2N;
	Complex *Data;

	IplImage *outputImage = cvCreateImage(cvGetSize(FFTSpectrum), 8, 1);

	Num = FFTSpectrum->width;
	Log2N = 0;
	while (Num >= 2) //Calculating the width of a frequency-converted image 
	{         //주파수 변환된 영상의 너비 계산
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[FFTSpectrum->height];
	IFFT = new Complex *[FFTSpectrum->height]; //Arrangement for an inversely transformed image
											   //역변환된 영상을 위한 배열
	for (i = 0; i < FFTSpectrum->height; i++) {
		IFFT[i] = new Complex[FFTSpectrum->width];
	}

	for (i = 0; i < FFTSpectrum->height; i++) {
		for (j = 0; j < FFTSpectrum->width; j++) { //Copy one row 한 행을 복사
			Data[j].Re = FFT[i][j].Re;
			Data[j].Im = FFT[i][j].Im;
		}
		IFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j < FFTSpectrum->width; j++) {
			IFFT[i][j].Re = Data[j].Re; //Save Results 결과 저장
			IFFT[i][j].Im = Data[j].Im;
		}
	}

	Num = FFTSpectrum->height;
	Log2N = 0;
	while (Num >= 2) //Calculation of height of frequency converted image
	{         //주파수 변환된 영상의 높이 계산
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[FFTSpectrum->height];

	for (i = 0; i < FFTSpectrum->width; i++) {
		for (j = 0; j < FFTSpectrum->height; j++) {
			Data[j].Re = IFFT[j][i].Re; //Copy one column 한 열을 복사
			Data[j].Im = IFFT[j][i].Im;
		}

		IFFT1d(Data, FFTSpectrum->width, Log2N); //1D RFFT

		for (j = 0; j < FFTSpectrum->width; j++) {//Save Results 결과 저장
			IFFT[j][i].Re = Data[j].Re;
			IFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < FFTSpectrum->width; i++) {
		for (j = 0; j < FFTSpectrum->height; j++) {
			cvSet2D(outputImage, i, j, cvScalar((unsigned char)IFFT[i][j].Re));
		}
	}
	delete[] Data;

	return outputImage;
}
void IFFT1d(Complex *X, int N, int Log2N)
{
	Scrambling(X, N, Log2N);
	Butterfly(X, N, Log2N, 2);
}

void OnSNR(IplImage * inputImage, IplImage * outputImage)
{
	double OrgSum, ErrSum, MeanErr, MeanOrg, SNR;
	CvScalar inVal, outVal;
	int i, j;

	OrgSum = 0.0;
	ErrSum = 0.0;

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			ErrSum += (cvGet2D(inputImage, i, j).val[0] - cvGet2D(outputImage, i, j).val[0]) * (cvGet2D(inputImage, i, j).val[0] - cvGet2D(outputImage, i, j).val[0]);
		}
	}

	MeanErr = (double)ErrSum / (inputImage->height * inputImage->width);

	for (i = 0; i < inputImage->height; i++) {
		for (j = 0; j < inputImage->width; j++) {
			OrgSum += cvGet2D(inputImage, i, j).val[0] * cvGet2D(inputImage, i, j).val[0];
		}
	}

	MeanOrg = (double)OrgSum / (inputImage->height * inputImage->width);

	SNR = 10 * (double)log10(MeanOrg / MeanErr);

	printf("%lf\n", SNR);
}