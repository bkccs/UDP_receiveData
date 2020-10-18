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
	char MBBH;//Ŀ����
	char MBSX;//Ŀ������
	double  MBJD;//Ŀ�꾭��
	double  MBWD;//Ŀ��γ��
	float MBGC;     //Ŀ��߳�
	int  LeftX;//���Ͻ�����X
	int  LeftY;//���Ͻ�����Y
	int  RightX;//���½�����X
	int  RightY;//���½�����Y
	float fConf; // ���Ŷ�
	float pfRes[8]; //����
}Struct_ZB;

typedef struct _Struct_SBJG_DC__
{
	char DH[4]; //����
	char MBSBGS;//Ŀ��ʶ�����
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
