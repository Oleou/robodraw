
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
	char* window_name = "Преобразователь";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	//Mat invert, src_gray;
	int c;

	/// получение изображения
	src = imread(argv[1]);

	if (!src.data)
	{
		return -1;
	}
	
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//equalizeHist(src, src);
	/// Преобразование в чб
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// Окошко
	namedWindow(window_name, CV_WINDOW_AUTOSIZE);

	/// Градиенты
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	
	//Собель
	/// X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Сумма градиентов
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	
	//Инверсия
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
// функция-обработчик ползунка - 
// порядок производной по X
void myTrackbarXorder(int pos) {
	xorder = pos;
}

//
// функция-обработчик ползунка - 
// порядок производной по Y
void myTrackbarYorder(int pos) {
	yorder = pos;
}

int main(int argc, char* argv[])
{
	// имя картинки задаётся первым параметром
	char* filename = argc >= 2 ? argv[1] : "Image0.jpg";
	// получаем картинку
	image = cvLoadImage(filename, 1);
	// создаём картинки
	dst = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_16S, image->nChannels);
	dst2 = cvCreateImage(cvSize(image->width, image->height), image->depth, image->nChannels);

	printf("[i] image: %s\n", filename);
	assert(image != 0);

	// окно для отображения картинки
	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("sobel", CV_WINDOW_AUTOSIZE);


	int aperture = argc == 3 ? atoi(argv[2]) : 3;

	cvCreateTrackbar("xorder", "sobel", &xorder, xorder_max, myTrackbarXorder);
	cvCreateTrackbar("yorder", "sobel", &yorder, yorder_max, myTrackbarYorder);

	while (1){

		// проверяем, чтобы порядок производных по X и Y был отличен от 0
		if (xorder == 0 && yorder == 0){
			printf("[i] Error: bad params for cvSobel() !\n");
			cvZero(dst2);
		}
		else{
			// применяем оператор Собеля
			cvSobel(image, dst, xorder, yorder, aperture);
			// преобразуем изображение к 8-битному
			cvConvertScale(dst, dst2);
			//GaussianBlur(dst2, dst2, Size(3, 3), 0, 0, BORDER_DEFAULT);
			
		}

		// показываем картинку
		cvShowImage("original", image);
		cvShowImage("sobel", dst2);

		char c = cvWaitKey(33);
		if (c == 27) { // если нажата ESC - выходим
			break;
		}
	}

	// освобождаем ресурсы
	cvReleaseImage(&image);
	cvReleaseImage(&dst);
	cvReleaseImage(&dst2);
	// удаляем окна
	cvDestroyAllWindows();
	return 0;
}
*/