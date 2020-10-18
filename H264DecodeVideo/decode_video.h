/*************************************************************************
	> File Name: decode_video.h
	> Author:zhou gang
	> Mail: aloneup@163.com
	>://item.jd.com/576925.html#none: Created Time: Wed 25 Apr 2018 10:28:51 PM PDT
 ************************************************************************/
#pragma once
#ifdef DLL_IMPLEMENT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#ifndef _DECODE_VIDEO_H
#define _DECODE_VIDEO_H

typedef struct _Struct_ZB_
{
	char MBBH;//目标编号
	char MBSX;//目标属性
	double  MBJD;//目标经度
	double  MBWD;//目标纬度
	float MBGC;     //目标高程
	int  LeftX;//左上角坐标X
	int  LeftY;//左上角坐标Y
	int  RightX;//右下角坐标X
	int  RightY;//右下角坐标Y
	float fConf; // 置信度
	float pfRes[8]; //保留
}Struct_ZB;

typedef struct _Struct_SBJG_DC__
{
	char DH[4]; //弹号
	char MBSBGS;//目标识别个数
	Struct_ZB * struct_ZB;
}Struct_SBJG_DC;


#include "opencv2/opencv.hpp"
DLL_API void objRecog(char DH, int &iInWidth, int &iInHeight, unsigned char * pInData, Struct_SBJG_DC * struct_SBJG_DC);
DLL_API uchar* bufferread(const char* buffer, int &size);
DLL_API void imgprocess(uchar *pInData, int iInDataLen, int &iOutWidth, int &iOutHeight, uchar * pOutData);
DLL_API void imgprocess_SAR(uchar *pInData, int iInDataLen, int &iOutWidth, int &iOutHeight, uchar * pOutData);
DLL_API void objRecog_SAR(char DH, int &iInWidth, int &iInHeight, unsigned char * pInData, Struct_SBJG_DC * struct_SBJG_DC);
DLL_API void Handle_Recog(char DH, int &iInWidth, int &iInHeight, unsigned char * pInData, Struct_SBJG_DC * struct_SBJG_DC, void(*Callback1)(char, int&, int&, unsigned char *, Struct_SBJG_DC *), void(*Callback2)(char, int&, int&, unsigned char *, Struct_SBJG_DC *));
DLL_API void Handle_Data(uchar *pInData, int iInDataLen, int &iOutWidth, int &iOutHeight, uchar * pOutData, void(*Callback1)(uchar *, int, int&, int&, uchar *), void(*Callback2)(uchar *, int, int&, int&, uchar *));
#endif
