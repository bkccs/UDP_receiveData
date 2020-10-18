#include "decode_video.h"
#include "DataChain.h"
#include "common.h"
#include <iostream>
#include <assert.h>
using namespace std;
//#define IRTEST
int main(void)
{
	DataChainCommonType test = { 0 };
	DataChainCommonType *testpoint;
	//OneFrameDecode a;
	//a.decode_oneframe_init();
	uchar*str;
	uchar*str1;
	uchar*out_data;
#ifdef IRTEST
	out_data = (uchar*)malloc(sizeof(uchar) * 1280 * 720 * 3 / 2);
#else
	out_data = (uchar*)malloc(sizeof(uchar) * 15360 * 4096 * 3 / 2);
#endif
	//pBGR24 = (uchar*)malloc(sizeof(uchar) * 320 * 256);
	int write_count = 0;
	int w;
	int h;
	int size_a = 0;
	int numb_a = 0;
	int restnum = 235;
#ifdef IRTEST
	str = bufferread("..\\DATA\\cuc_ieschool.h265", size_a);//test_h265.h265//cuc_ieschool//1//cuc_ieschool_adddata
#else
	str = bufferread("..\\DATA\\test333.mjpeg", size_a);//cuc_view_encode//outm//stream_chn0
#endif
	str1 = (uchar*)malloc(sizeof(uchar) * 243);
	//for (int i = 0; i < 10; i++)//循环十次，仅为测试。
	//{
//		write_count = 0;
//		while (numb_a * 235 < size_a + 235)
//		{
//			if (numb_a * 235 < size_a)
//			{
//				restnum = 235;
//				memcpy(str1, str + numb_a * 235, 235);
//			}
//			if (numb_a * 235 > size_a && numb_a * 235 < size_a + 235)
//			{
//				memset(str1,0,235);
//				restnum = size_a - (numb_a - 1) * 235;
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
//#ifdef IRTEST
//			test.ID_SRC = 0X11;
//#else
//			test.ID_SRC = 0X22;
//#endif
		while (numb_a * 243 < size_a)
		{
			if (numb_a * 243 < size_a)
			{
				restnum = 235;
				memcpy(str1, str + numb_a * 243, 243);
				testpoint = (DataChainCommonType*)str1;
				cout << u8u16(testpoint->NUMB.data_u8) << endl;
			}
			//uchar* pChar = (uchar*)&test;
			//memcpy(str1, pChar, sizeof(DataChainCommonType));
			Handle_Data(str1, restnum+8, w, h, out_data, imgprocess, imgprocess_SAR);
			cv::Mat yuvyyy(h * 3 / 2, w, CV_8UC1);
			cv::Mat dst(h, w, CV_8UC1);
			if (h > 0 && w > 0)
			{
				_Struct_SBJG_DC__ *inputdata = (_Struct_SBJG_DC__ *)malloc(sizeof(_Struct_SBJG_DC__));
				inputdata->struct_ZB = (_Struct_ZB_ *)malloc(sizeof(_Struct_ZB_));
				//init();
				//YV12ToBGR24_FFmpeg(out_data, pBGR24, w, h);
				memcpy(yuvyyy.data, out_data, h * w * 3 / 2 * sizeof(uchar));
				cv::cvtColor(yuvyyy, dst, CV_YUV2BGR_I420);
				Handle_Recog(0, w, h, out_data, inputdata, objRecog, objRecog_SAR);
				cv::rectangle(dst, cv::Point(inputdata->struct_ZB->LeftX, inputdata->struct_ZB->LeftY), cv::Point(inputdata->struct_ZB->RightX, inputdata->struct_ZB->RightY), cv::Scalar(0, 0, 255), 2, 8, 0);
				//char testaaa = dst.at<char>(0, 0);
				cv::imshow("testYUV", dst);
				cv::imwrite("testYUV.bmp", dst);
				cv::waitKey(0);
				cv::cvtColor(dst, dst, CV_BGR2GRAY);
				cv::imwrite("C:\\Users\\dream\\Desktop\\datah265\\res\\"+to_string(write_count)+".bmp", dst);
				write_count++;
				free(inputdata->struct_ZB);
				free(inputdata);
			}
			yuvyyy.release();
			dst.release();
			numb_a++;
		}
		numb_a = 0;
	//}

	return 0;
}


