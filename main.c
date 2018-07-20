	#include "opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include<opencv2/video/video.hpp>
#include"opencv2/highgui/highgui.hpp"
#include<fstream>
#include<iostream>
// #include <highgui.h>
// #include <cxcore.h>  
// #include "cvcam.h"  
// #include <windows.h>  
// #include <cv.h>  
// #include "cv.h"
// #include "highgui.h"
char wndname[] = "Edge";
char tbarname[] = "Threshold";
int edge_thresh = 31;
IplImage *image = 0, *cedge = 0, *gray = 0, *edge = 0;
// 定义跟踪条的 callback 函数
void on_trackbar(int h)
{
    cvSmooth( gray, edge, CV_BLUR, 3, 3, 0 );
    cvNot( gray, edge );
    // 对灰度图像进行边缘检测
    cvCanny(gray, edge, (float)edge_thresh, (float)edge_thresh*3, 3);
    cvZero( cedge );
    // copy edge points
    cvCopy( image, cedge, edge );
    // 显示图像
    cvShowImage(wndname, cedge);
}
int main( int argc, char** argv )
{
    // char* filename = argc == 2 ? argv[1] : (char*)"fruits.jpg";
    
    // if( (image = cvLoadImage( filename, 1)) == 0 )
        // return -1;
	
	
	IplImage *pFrame = NULL, *srcImage=NULL;

	CvCapture *pCapture = NULL;
	cv::Mat mat_trasfor ;
	// input like this rtsp://192.168.11.124/stream_chn0.h264
	pCapture =cvCreateFileCapture("rtsp://192.168.11.124/stream_chn0.h264");//your own rtsp address
	
	if(!pCapture){
		printf("Can not get the videostream from the camera!\n");
		return -1;
	}
	
	while (1){
		pFrame = cvQueryFrame(pCapture);
		srcImage=cvCloneImage(pFrame);
		cv::Mat matimg = cv::Mat(srcImage);	
		
		resize (matimg ,mat_trasfor ,cv::Size(matimg.cols/3 , matimg.rows/3),(0,0),(0,0),3 );
		
		IplImage iplimg2 = IplImage(mat_trasfor);	
		
		imshow("mat_trasfor ", mat_trasfor);
		cvShowImage("rtsp_test",&iplimg2);

		image=cvCloneImage(&iplimg2);






		
		
		// Create the output image
		cedge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 3);
		// 将彩色图像转换为灰度图像
		gray = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
		edge = cvCreateImage(cvSize(image->width,image->height), IPL_DEPTH_8U, 1);
		cvCvtColor(image, gray, CV_BGR2GRAY);
		// Create a window
		cvNamedWindow(wndname, 1);
		// create a toolbar 
		cvCreateTrackbar(tbarname, wndname, &edge_thresh, 100, on_trackbar);
		// Show the image
		on_trackbar(1);
		// Wait for a key stroke; the same function arranges events processing
		cvWaitKey(10);		
		
	    cvReleaseImage(&image);
		cvReleaseImage(&gray);
		cvReleaseImage(&edge);	
		
		
		cvWaitKey(10);
		// cvReleaseImage((IplImage**)(&&iplimg2));
		// iplimg2=NULL;
		cvReleaseImage(&srcImage);
		srcImage=NULL;
		
	}
	
	cvReleaseCapture(&pCapture);
	cvReleaseImage(&pFrame);
    cvDestroyWindow(wndname);
    return 0;
}

