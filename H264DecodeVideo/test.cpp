//#include "decode_video.h"
//#include "DataChain.h"
//#include "common.h"
//#include <iostream>
//#include <assert.h>
//using namespace std;
//static void YUV422p_to_RGB24(unsigned char *yuv422[3], unsigned char *rgb24, int width, int height);
//#define IRTEST
//int main(void)
//{
//	DataChainCommonType test = { 0 };
//	//OneFrameDecode a;
//	//a.decode_oneframe_init();
//	uchar*str;
//	uchar*str1;
//	uchar*out_data;
//#ifdef IRTEST
//	out_data = (uchar*)malloc(sizeof(uchar) * 1640 * 1512 * 3 / 2);
//#else
//	//out_data = (uchar*)malloc(sizeof(uchar) * 854 * 480 * 3 / 2 * 16);
//	out_data = (uchar*)malloc(sizeof(uchar) * 15360 * 4096 * 3 / 2);
//#endif
//	//pBGR24 = (uchar*)malloc(sizeof(uchar) * 320 * 256);
//	int write_count = 0;
//	int w;
//	int h;
//	int size_a = 0;
//	int numb_a = 0;
//	//FILE *fp = fopen("..\\DATA\\decode20201009.h265", "wb+");
//#ifdef IRTEST
//	str = bufferread("..\\DATA\\cuc_ieschool_adddata.h265", size_a);//test_h265.h265//cuc_ieschool//1//cuc_ieschool_adddata
//#else
//	str = bufferread("..\\DATA\\test_taiyuan.mjpeg", size_a);//cuc_view_encode//outm
//#endif
//	str1 = (uchar*)malloc(sizeof(uchar) * 243);
//	//for (int i = 0; i < 10; i++)//循环十次，仅为测试。
//	{
//		write_count = 0;
//		while (numb_a * 235 < size_a + 235)
//		{
//			if (numb_a * 235 < size_a)
//			{
//				memcpy(str1, str + numb_a * 235, 235);
//			}
//			if (numb_a * 235 > size_a && numb_a * 235 < size_a + 235)
//			{
//				int restnum = size_a - (numb_a - 1) * 235;
//				memcpy(str1, str + numb_a * 235, restnum);
//			}
//			//a.decode_oneframe(str1, 235);
//			for (int i = 0; i < 235; i++)
//			{
//				test.data[i] = str1[i];
//			}
//			if (numb_a == 0)
//			{
//				test.NUMB.data_u8[0] = 1;
//			}
//			else
//			{
//				test.NUMB.data_u8[0] = 2;
//			}
//			test.DataLength = 240;
//#ifdef IRTEST
//			test.ID_SRC = 0X11;
//#else
//			test.ID_SRC = 0X12;
//#endif
//			uchar* pChar = (uchar*)&test;
//			memcpy(str1, pChar, sizeof(DataChainCommonType));
//			Handle_Data(str1, 243, w, h, out_data, imgprocess, imgprocess_SAR);
//			cv::Mat dst(h, w, CV_8UC1);
//			if (h > 0 && w > 0)
//			{
//				//_Struct_SBJG_DC__ *inputdata = (_Struct_SBJG_DC__ *)malloc(sizeof(_Struct_SBJG_DC__));
//				//inputdata->struct_ZB = (_Struct_ZB_ *)malloc(sizeof(_Struct_ZB_));
//				//Handle_Recog(0, w, h, out_data, inputdata, objRecog, objRecog_SAR);
//				//init();
//				//YV12ToBGR24_FFmpeg(out_data, pBGR24, w, h);
//				memcpy(dst.data, out_data, h * w * 1 * sizeof(uchar));
//
//				//cv::cvtColor(yuvyyy, dst, CV_YUV2BGR_I420);
//				//cv::rectangle(dst, cv::Point(inputdata->struct_ZB->LeftX, inputdata->struct_ZB->LeftY), cv::Point(inputdata->struct_ZB->RightX, inputdata->struct_ZB->RightY), cv::Scalar(0, 0, 255), 2, 8, 0);
//				//char testaaa = dst.at<char>(0, 0);
//				//cv::cvtColor(dst, dst, CV_BGR2GRAY);
//				cv::imshow("testYUV", dst);
//				cv::waitKey(33);
//				//cv::imwrite("C:\\Users\\dream\\Desktop\\datah265\\res\\"+to_string(write_count)+".bmp", dst);
//
//				//cv::cvtColor(dst, dst, CV_BGR2GRAY);
//				//cv::imwrite("..\\DATA\\0.bmp", dst);
//				write_count++;
//				printf("success");
//				//free(inputdata->struct_ZB);
//				//free(inputdata);
//			}
//			dst.release();
//			numb_a++;
//		}
//		numb_a = 0;
//	}
//
//	return 0;
//}
//static void YUV422p_to_RGB24(unsigned char *yuv422[3], unsigned char *rgb24, int width, int height)
//{
//	int R, G, B, Y, U, V;
//	int x, y;
//	int nWidth = width >> 1; //色度信号宽度
//	for (y = 0; y<height; y++)
//	{
//		for (x = 0; x<width; x++)
//		{
//			Y = *(yuv422[0] + y*width + x);
//			U = *(yuv422[1] + y*nWidth + (x >> 1));
//			V = *(yuv422[2] + y*nWidth + (x >> 1));
//			R = Y + 1.402*(V - 128);
//			G = Y - 0.34414*(U - 128) - 0.71414*(V - 128);
//			B = Y + 1.772*(U - 128);
//
//			//防止越界
//			if (R>255)R = 255;
//			if (R<0)R = 0;
//			if (G>255)G = 255;
//			if (G<0)G = 0;
//			if (B>255)B = 255;
//			if (B<0)B = 0;
//
//			*(rgb24 + ((height - y - 1)*width + x) * 3) = B;
//			*(rgb24 + ((height - y - 1)*width + x) * 3 + 1) = G;
//			*(rgb24 + ((height - y - 1)*width + x) * 3 + 2) = R;
//		}
//	}
//}



//#include "thread"
//#include "decode_video.h"
//#include "DataChain.h"
//#include "common.h"
//#include <iostream>
//#include <assert.h>
//using namespace std;
//cv::Mat thread_show;
//int istesting = true;
//int isimgready = false;
//void thread_imgshow()
//{
//	while (istesting)
//	{
//		if (isimgready)
//		{
//			cv::imshow("111", thread_show);
//			cv::waitKey(0);
//		}
//
//	}
//
//}
////#define IRTEST
//int main(void)
//{
//	thread th1(thread_imgshow);
//	th1.detach();
//	DataChainCommonType test = { 0 };
//	//OneFrameDecode a;
//	//a.decode_oneframe_init();
//	uchar*str;
//	uchar*str1;
//	uchar*out_data;
//#ifdef IRTEST
//	out_data = (uchar*)malloc(sizeof(uchar) * 1640 * 1512 * 3 / 2);
//#else
//	//out_data = (uchar*)malloc(sizeof(uchar) * 854 * 480 * 3 / 2 * 16);
//	out_data = (uchar*)malloc(sizeof(uchar) * 16384 * 4096 * 3 / 2);
//#endif
//	//pBGR24 = (uchar*)malloc(sizeof(uchar) * 320 * 256);
//	int write_count = 0;
//	int w;
//	int h;
//	int size_a = 0;
//	int numb_a = 0;
//	FILE *fp = fopen("..\\DATA\\decode20201009.mjpeg", "wb+");
//#ifdef IRTEST
//	str = bufferread("..\\DATA\\02\\test265.h265", size_a);//test_h265.h265//cuc_ieschool//1//cuc_ieschool_adddata
//#else
//	str = bufferread("C:\\Users\\dream\\Desktop\\datah265\\testHK.dat", size_a);//cuc_view_encode//outm
//#endif
//	str1 = (uchar*)malloc(sizeof(uchar) * 243);
////	//for (int i = 0; i < 10; i++)//循环十次，仅为测试。
////	{
////		write_count = 0;
////		while (numb_a * 235 < size_a + 235)
////		{
////			if (numb_a * 235 < size_a)
////			{
////				memcpy(str1, str + numb_a * 235, 235);
////			}
////			if (numb_a * 235 > size_a && numb_a * 235 < size_a + 235)
////			{
////				int restnum = size_a - (numb_a - 1) * 235;
////				memcpy(str1, str + numb_a * 235, restnum);
////			}
////			//a.decode_oneframe(str1, 235);
////			for (int i = 0; i < 235; i++)
////			{
////				test.data[i] = str1[i];
////			}
////			if (numb_a == 0)
////			{
////				test.NUMB.data_u8[0] = 1;
////			}
////			else
////			{
////				test.NUMB.data_u8[0] = 2;
////			}
////#ifdef IRTEST
////			test.ID_SRC = 0X11;
////#else
////			test.ID_SRC = 0X12;
////#endif
////			uchar* pChar = (uchar*)&test;
////			memcpy(str1, pChar, sizeof(DataChainCommonType));
//	while (numb_a * 243 < size_a + 243)
//	{
//		if (numb_a * 243 < size_a)
//		{
//			memcpy(str1, str + numb_a * 243, 243);
//		}
//		//fwrite(str1 + 7, (int)(str[2]-5), 1, fp);
//		Handle_Data(str1, 243, w, h, out_data, imgprocess, imgprocess_SAR);
//		cv::Mat yuvyyy(h * 3 / 2, w, CV_8UC1);
//		cv::Mat dst(h, w, CV_8UC1);
//		if (h > 0 && w > 0)
//		{
//			_Struct_SBJG_DC__ *inputdata = (_Struct_SBJG_DC__ *)malloc(sizeof(_Struct_SBJG_DC__));
//			inputdata->struct_ZB = (_Struct_ZB_ *)malloc(sizeof(_Struct_ZB_));
//			//Handle_Recog(0, w, h, out_data, inputdata, objRecog, objRecog_SAR);
//			//init();
//			//YV12ToBGR24_FFmpeg(out_data, pBGR24, w, h);
//			memcpy(yuvyyy.data, out_data, h * w * 3 / 2 * sizeof(uchar));
//			cv::cvtColor(yuvyyy, dst, CV_YUV2BGR_I420);
//			//thread_show = dst;
//			//isimgready = true;
//			//cv::rectangle(dst, cv::Point(inputdata->struct_ZB->LeftX, inputdata->struct_ZB->LeftY), cv::Point(inputdata->struct_ZB->RightX, inputdata->struct_ZB->RightY), cv::Scalar(0, 0, 255), 2, 8, 0);
//			//char testaaa = dst.at<char>(0, 0);
//			//cv::imshow("testYUV", dst);
//			//cv::waitKey(1);
//			//cv::imwrite("C:\\Users\\dream\\Desktop\\datah265\\res\\" + to_string(write_count) + ".bmp", dst);
//
//			cv::cvtColor(dst, dst, CV_BGR2GRAY);
//			cv::imwrite("..\\DATA\\0.bmp", dst);
//			write_count++;
//			printf("success");
//			free(inputdata->struct_ZB);
//			free(inputdata);
//		}
//		yuvyyy.release();
//		dst.release();
//		numb_a++;
//	}
//	numb_a = 0;
//	fclose(fp);
//	return 0;
//}









#include "thread"
#include "Deque_Buffer.h"
#include "decode_video.h"
#include "DataChain.h"
#include "common.h"
#include <iostream>
#include <assert.h>
#include "Receive.h"
#include <fstream>//ifstream读文件，ofstream写文件，fstream读写文件
#include <string>//文本对象，储存读取的内容
#include <iostream>//屏幕输出cout
#include <cstdlib>//调用system("pause");
#include <windows.h>//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
using namespace std;
cv::Mat thread_show;
BOOL istesting = true;
BOOL isgetframe = false;
BOOL isimgready = false;
uchar*str1;
uchar*str;
uchar*str2 = NULL;
uchar*str3 = NULL;
int w;
int h;
int size_a;
int count2 = 0;
uchar*out_data;
Deque_Buffer a;
Receive receive;
char* strMessage = (char*)malloc(sizeof(char) * 243);
void thread_getimg()
{
	while (1)
	{
		str2 = a.popFrontFrom_dequeBuffUse();
		if (str2)
		{
			//memcpy(str3, str2,243);
			Handle_Data(str2, 243, w, h, out_data, imgprocess, imgprocess_SAR);
			if (w*h > 0)
			{
				cv::Mat yuvyyy(h * 3 / 2, w, CV_8UC1);
				cv::Mat dst(h, w, CV_8UC3);
				//_Struct_SBJG_DC__ *inputdata = (_Struct_SBJG_DC__ *)malloc(sizeof(_Struct_SBJG_DC__));
				//inputdata->struct_ZB = (_Struct_ZB_ *)malloc(sizeof(_Struct_ZB_));
				//init();
				//YV12ToBGR24_FFmpeg(out_data, pBGR24, w, h);
				memcpy(yuvyyy.data, out_data, h * w * 3 / 2 * sizeof(uchar));
				cv::cvtColor(yuvyyy, dst, CV_YUV2BGR_I420);
				cv::imwrite("..\\DATA\\SAR1018.jpg", dst);
				//thread_show = dst;
				//cv::imshow("111", dst);
				//cv::waitKey(1);
				//isimgready = false;
			}
			memset(str2, 0, 243);
			a.pushBackTo_dequeBuffEmpty(str2);
		}
		else
		{
			//cv::waitKey(1);
		}


	}
}

void thread_imgshow()
{
	while (istesting)
	{
		if (isimgready)
		{
			if (w*h > 0)
			{
				cv::Mat yuvyyy(h * 3 / 2, w, CV_8UC1);
				cv::Mat dst(h, w, CV_8UC3);
				//_Struct_SBJG_DC__ *inputdata = (_Struct_SBJG_DC__ *)malloc(sizeof(_Struct_SBJG_DC__));
				//inputdata->struct_ZB = (_Struct_ZB_ *)malloc(sizeof(_Struct_ZB_));
				//init();
				//YV12ToBGR24_FFmpeg(out_data, pBGR24, w, h);
				memcpy(yuvyyy.data, out_data, h * w * 3 / 2 * sizeof(uchar));
				cv::cvtColor(yuvyyy, dst, CV_YUV2BGR_I420);
				cv::imwrite("..\\DATA\\SAR1018.jpg", dst);
				//thread_show = dst;
				//cv::imshow("111", dst);
				//cv::waitKey(1);
				//isimgready = false;
			}
		}
	}

}

void thread_getframe()
{

	while (1)
	{

		if (receive.ReceiveStringData(strMessage))
		{

			if (!(str1 = a.popFrontFrom_dequeBuffEmpty()))
				str1 = a.popFrontFrom_dequeBuffUse();
			memcpy(str1, strMessage, 243);
			count2 += 243;
			//isgetframe = true;
			a.pushBackTo_dequeBuffUse(str1);
			//for (int i = 0; i < 1000000; i++)
			//{

			//}
		}
		//receive.ReceiveStringData(strMessage);

		//for (int ii = 0; ii < 243; ii++)
		//{
		//	str1[ii] = strMessage[ii];
		//}

		//isgetframe = true;
		//cv::waitKey(1);
		//str1 = (uchar*)strMessage;


		//for (int aj = 0; aj < 5; aj++)
		//{

		//	Handle_Data(str1 + aj * 243, 243, w, h, out_data, imgprocess, imgprocess_SAR);
		//	if (h > 0 && w > 0)
		//	{
		//		isimgready = true;
		//	}
		//}
		//for (int ii = 0; ii < 243; ii++)
		//{
		//	str1[ii] = strMessage[ii];
		//}

		//memcpy(str1, (unsigned char*)strMessage, 243 * sizeof(uchar));
		//		cout << "get one packet: " << endl;



		//yuvyyy.release();
		//dst.release();
	}
}


int main(void)
{
	str3 = (uchar*)malloc(sizeof(uchar) * 243);
	out_data = (uchar*)malloc(sizeof(uchar) * 16384 * 4096 * 3 / 2);
	int write_count = 0;
	count2 = 0;
	str = bufferread("..\\DATA\\test265.h265", size_a);

	a.Init_buffer();

	memset(strMessage, 0, 243);

	if (receive.InitSocket("226.0.0.22", "7041"))
	{
		cout << "UDP Init success!" << endl;
	}
	else
	{
		cout << "Init Failed" << endl;
		return -1;
	}
	system("pause");
	thread th1(thread_getimg);
	th1.detach();
	thread th2(thread_getframe);
	th2.detach();
	//thread th3(thread_imgshow);
	//th3.detach();

	//	while (1)
	//	{
	//		str1 = a.popFrontFrom_dequeBuffEmpty();
	//		if (count2 < size_a)
	//		{
	//			if (str1)
	//			{
	//				memcpy(str1, str + count2, 243);
	//				count2 += 243;
	//			}
	//			//isgetframe = true;
	//			//cv::waitKey(1);
	//		}
	//		//receive.ReceiveStringData(strMessage);
	//		
	//		//for (int ii = 0; ii < 243; ii++)
	//		//{
	//		//	str1[ii] = strMessage[ii];
	//		//}
	//		a.pushBackTo_dequeBuffUse(str1);
	//		isgetframe = true;
	//		cv::waitKey(10);
	//		//str1 = (uchar*)strMessage;
	//
	//
	//		//for (int aj = 0; aj < 5; aj++)
	//		//{
	//
	//		//	Handle_Data(str1 + aj * 243, 243, w, h, out_data, imgprocess, imgprocess_SAR);
	//		//	if (h > 0 && w > 0)
	//		//	{
	//		//		isimgready = true;
	//		//	}
	//		//}
	//		//for (int ii = 0; ii < 243; ii++)
	//		//{
	//		//	str1[ii] = strMessage[ii];
	//		//}
	//
	//		//memcpy(str1, (unsigned char*)strMessage, 243 * sizeof(uchar));
	////		cout << "get one packet: " << endl;
	//
	//
	//
	//		//yuvyyy.release();
	//		//dst.release();
	//	}

	while (1)
	{
		if (w*h > 0)
		{
			isimgready = true;
		}
	}
	receive.CloseSocket();
	free(strMessage);
	return 0;
	//
	//const char * filePath = "D:\\0_Work\\one-shot-siamese-master\\data\\mini-imagenet\\images_color\\1.txt";
	//string floderPath = "D:\\0_Work\\one-shot-siamese-master\\data\\mini-imagenet\\images_color\\";
	//string outPath = "D:\\0_Work\\one-shot-siamese-master\\data\\mini-imagenet\\images\\";
	//SetConsoleOutputCP(65001);
	//ifstream in(filePath);
	//string line;
	//
	//if (in) // 有该文件
	//{
	//	while (getline(in, line)) // line中不包括每行的换行符
	//	{
	//		cv::Mat output;
	//		cv::Mat input = cv::imread(floderPath+line,-1);
	//		//cv::cvtColor(input, output, CV_BGR2GRAY);
	//		cv::resize(input, input, cv::Size(105, 105), 0, 0, cv::INTER_LINEAR);
	//		cv::imwrite(outPath + line, input);
	//	}
	//}
	//else // 没有该文件
	//{
	//	cout << "no such file" << endl;
	//}
	//
	//system("pause");

}


