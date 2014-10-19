
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char** argv)
{

	Mat src, src_gray;
	Mat grad;
	char* window_name = "���������������";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	//Mat invert, src_gray;
	int c;

	/// ��������� �����������
	src = imread(argv[1]);

	if (!src.data)
	{
		return -1;
	}
	
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//equalizeHist(src, src);
	/// �������������� � ��
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// ������
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// ���������
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	
	//������
	/// X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// ����� ����������
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	
	//��������
	bitwise_not(grad, grad);

	imshow(window_name, grad);
	waitKey(0);

	return 0;
}

/////////////////////////////////////////////////

/*

IplImage* image = 0;
IplImage* dst = 0;
IplImage* dst2 = 0;

int xorder = 1;
int xorder_max = 2;

int yorder = 1;
int yorder_max = 2;

//
// �������-���������� �������� - 
// ������� ����������� �� X
void myTrackbarXorder(int pos) {
	xorder = pos;
}

//
// �������-���������� �������� - 
// ������� ����������� �� Y
void myTrackbarYorder(int pos) {
	yorder = pos;
}

int main(int argc, char* argv[])
{
	// ��� �������� ������� ������ ����������
	char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
	// �������� ��������
	image = cvLoadImage(filename, 1);
	// ������ ��������
	dst = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_16S, image->nChannels);
	dst2 = cvCreateImage(cvSize(image->width, image->height), image->depth, image->nChannels);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// ���� ��� ����������� ��������
	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sobel", CV_WINDOW_AUTOSIZE);


	int aperture = argc == 3 ? atoi(argv[2]) : 3;

	cvCreateTrackbar("xorder", "sobel", &xorder, xorder_max, myTrackbarXorder);
	cvCreateTrackbar("yorder", "sobel", &yorder, yorder_max, myTrackbarYorder);

	while (1){

		// ���������, ����� ������� ����������� �� X � Y ��� ������� �� 0
		if (xorder == 0 && yorder == 0){
			printf("[i] Error: bad params for cvSobel() !\n");
			cvZero(dst2);
		}
		else{
			// ��������� �������� ������
			cvSobel(image, dst, xorder, yorder, aperture);
			// ����������� ����������� � 8-�������
			cvConvertScale(dst, dst2);
			//GaussianBlur(dst2, dst2, Size(3, 3), 0, 0, BORDER_DEFAULT);
			
		}

		// ���������� ��������
		cvShowImage("original", image);
		cvShowImage("sobel", dst2);

		char c = cvWaitKey(33);
		if (c == 27) { // ���� ������ ESC - �������
			break;
		}
	}

	// ����������� �������
	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	// ������� ����
	cvDestroyAllWindows();
	return 0;
}
*/