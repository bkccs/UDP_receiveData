/*************************************************************************
	> File Name: decode_video.cpp
	> Author:zhou gang
	> Mail: aloneup@163.com
	> Created Time: Wed 25 Apr 2018 10:29:07 PM PDT
 ************************************************************************/
#include "decode_video.h"
#include "common.h"
#include "DataChain.h"
int isFirstPack = -1;
int isLastPack = 0;
int width_out = 0;
int height_out = 0;
using namespace std;
uchar* yuvimg_out = NULL;
uchar* video_bufglobal = NULL;
DataChainCommonType DataChainAllData = { 0 };
uint8_t *cur_ptr;
uint8_t *cur_ptr_head;
OneFrameDecode decode1;
G_DECODE_VIDEO_H video_t* video_init(uchar* video_buffer, int datalen, int *ret)
{
	//video_bufglobal = img_unpack(video_buffer, datalen);
	video_bufglobal = video_buffer;
	video_t* video_info = (video_t*)malloc(sizeof(video_t));
	video_info->packet = NULL;
	video_info->pAvFrame = NULL;
	video_info->pCodec = NULL;
	video_info->pFormatCtx = NULL;
	video_info->pCodecCtx = NULL;
	video_info->img_convert_ctx = NULL;
	video_info->videoindex = -1;
	video_info->pFormatCtx = avformat_alloc_context();
	av_register_all();
	unsigned char * iobuffer = (unsigned char *)av_malloc(datalen);
	AVIOContext *avio = avio_alloc_context(iobuffer, datalen, 0, NULL, fill_iobuffer, NULL, NULL);
	video_info->pFormatCtx->pb = avio;
	if (avformat_open_input(&(video_info->pFormatCtx), "nothing", NULL, NULL) != 0)
	{
		//无法打开文件
		(*ret) = -1;
		return NULL;
	}
	if (avformat_find_stream_info(video_info->pFormatCtx, NULL) < 0)
	{
		//无法查找到流信息
		(*ret) = -2;
		return NULL;
	}
	for (int i = 0; i < video_info->pFormatCtx->nb_streams; i++)
	{

		if (video_info->pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			video_info->videoindex = i;
			break;
		}
	}
	if (video_info->videoindex == -1)
	{
		//无法找到视频流
		(*ret) = -3;
		return NULL;
	}
	video_info->pCodecCtx = video_info->pFormatCtx->streams[video_info->videoindex]->codec;

	video_info->pCodec = avcodec_find_decoder(video_info->pCodecCtx->codec_id);
	if (video_info->pCodec == NULL)
	{
		(*ret) = -4;
		return NULL;
	}

	if (avcodec_open2(video_info->pCodecCtx, video_info->pCodec, NULL) < 0)
	{
		//无法打开解码器
		(*ret) = -5;
		return NULL;
	}
	video_info->pAvFrame = av_frame_alloc();
	int y_size = video_info->pCodecCtx->width * video_info->pCodecCtx->height;
	video_info->packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	av_new_packet(video_info->packet, y_size);
	(*ret) = 0;
	//
	return video_info;

}

void video_getimg(AVCodecContext * pCodecCtx, SwsContext * img_convert_ctx, AVFrame * pFrame, cv::Mat* pCvMat)
{
	if (pCvMat->empty())
	{
		pCvMat->create(cv::Size(pCodecCtx->width, pCodecCtx->height), CV_8UC3);
	}

	AVFrame *pFrameRGB = NULL;
	uint8_t  *out_bufferRGB = NULL;
	pFrameRGB = av_frame_alloc();

	//给pFrameRGB帧加上分配的内存;
	int size = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);
	out_bufferRGB = new uint8_t[size];
	avpicture_fill((AVPicture *)pFrameRGB, out_bufferRGB, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);

	//YUV to RGB
	sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

	memcpy(pCvMat->data, out_bufferRGB, size);

	delete[] out_bufferRGB;
	av_free(pFrameRGB);
}

G_DECODE_VIDEO_H int video_get_frame(video_t* handel, cv::Mat* pCvMat)
{
	int result = 0;
	int pic_got = -1;
	result = av_read_frame(handel->pFormatCtx, handel->packet);
	if (result < 0)
	{
		//视频播放完成
		pCvMat = NULL;
		return -6;
	}
	//此处需注意，视频播放完成后，并不会输出-6，而是会再进行解码导致解码错误输出-7
	if (handel->packet->stream_index == handel->videoindex)
	{
		int state = avcodec_decode_video2(handel->pCodecCtx, handel->pAvFrame, &pic_got, handel->packet);
		if (state < 0)
		{
			//解码错误
			pCvMat = NULL;
			return 0;
		}
		if (pic_got)
		{
			if (handel->img_convert_ctx == NULL)
			{
				handel->img_convert_ctx = sws_getContext(handel->pCodecCtx->width, handel->pCodecCtx->height, handel->pCodecCtx->pix_fmt, handel->pCodecCtx->width, handel->pCodecCtx->height, AV_PIX_FMT_GRAY8, SWS_BICUBIC, NULL, NULL, NULL);
			}
			if (pCvMat->empty())
			{
				pCvMat->create(cv::Size(handel->pCodecCtx->width, handel->pCodecCtx->height), CV_8UC1);
			}

			if (handel->img_convert_ctx != NULL)
			{
				video_getimg(handel->pCodecCtx, handel->img_convert_ctx, handel->pAvFrame, pCvMat);
			}
		}
	}
	av_free_packet(handel->packet);
	return 0;
}

G_DECODE_VIDEO_H int video_get_alltime(video_t* handel)
{
	int hours, mins, secs, us;
	if (handel->pFormatCtx->duration != AV_NOPTS_VALUE)
	{
		int64_t duration = handel->pFormatCtx->duration + 5000;
		secs = duration / AV_TIME_BASE;
		us = duration % AV_TIME_BASE;
		mins = secs / 60;
		secs %= 60;
		hours = mins / 60;
		mins %= 60;
		return (hours * 3600 + mins * 60 + secs);
	}
	else
	{
		return 0;
	}
}

G_DECODE_VIDEO_H int video_seek_frame(video_t* handel, long time_start)
{
	int64_t seek_pos = 0;
	if (time_start < 0)
	{
		return -1;
	}
	seek_pos = time_start * AV_TIME_BASE;
	if (handel->pFormatCtx->start_time != AV_NOPTS_VALUE)
	{
		seek_pos += handel->pFormatCtx->start_time;
	}
	if (av_seek_frame(handel->pFormatCtx, -1, seek_pos, AVSEEK_FLAG_ANY) < 0)
	{
		return -2;
	}
	return 0;
}

G_DECODE_VIDEO_H int video_uninit(video_t* handel)
{
	if (handel != NULL)
	{
		av_free_packet(handel->packet);
		avcodec_close(handel->pCodecCtx);
		avformat_close_input(&(handel->pFormatCtx));
		return 0;
	}
	else
	{
		return -1;
	}
}

//G_DECODE_VIDEO_H cv::Mat imgprocess()
//{
//
//}

int fill_iobuffer(void * opaque, uint8_t *buf, int bufsize)
{
	if (video_bufglobal)
	{
		memcpy(buf, video_bufglobal, bufsize);
		video_bufglobal = NULL;
		return bufsize;
	}
	else
	{
		return -1;
	}
}

uchar* bufferread(uchar* a_buffer, int &size)
{
	FILE * pFile;
	long lSize;
	size_t result;
	uchar* buffer;
	/* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
	pFile = fopen("C:\\Users\\dream\\Desktop\\datah265\\cuc_ieschool.h265", "rb");//test_h265.h265////cuc_ieschool
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		exit(1);
	}

	/* 获取文件大小 */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* 分配内存存储整个文件 */
	buffer = (uchar*)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		exit(2);
	}

	/* 将文件拷贝到buffer中 */
	result = fread(buffer, 1, lSize, pFile);

	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}
	size = lSize;
	/* 现在整个文件已经在buffer中，可由标准输出打印内容 */
	//printf("%s", buffer);
	/* 结束演示，关闭文件并释放内存 */
	fclose(pFile);
	return buffer;
}
uchar* OneFrameDecode::img_unpack(uchar* video_buffer, int bufsize)
{
	memcpy(&DataChainAllData, video_buffer, bufsize);
	uchar * zipData;
	zipData = (uchar *)malloc(sizeof(uchar)*bufsize);
	if (u8u16(DataChainAllData.NUMB.data_u8) == 1 && isFirstPack == -1)
	{
		isFirstPack = 1;
	}
	else if (u8u16(DataChainAllData.NUMB.data_u8) == 1 && isFirstPack != -1)
	{
		isFirstPack = 1;
		isLastPack = 1;
	}
	//zipDatavector.resize(ImgDataPack.size());
	memcpy(zipData, DataChainAllData.data, bufsize - 8);
	return zipData;
}
void buffer_fresh(uchar* a_buffer, int &size)
{
	video_bufglobal = a_buffer;
}



/**************************************************************/
void OneFrameDecode::decode_oneframe(uchar* video_buffer, int datalen)
{
	cur_size += datalen;
	cout << "cur_size = " << cur_size << endl;
	memcpy(cur_ptr + (cur_size - datalen), video_buffer, datalen);

	while (cur_size > 0)
	{

		len = av_parser_parse2(
			pCodecParserCtx, pCodecCtx,
			&packet.data, &packet.size,
			cur_ptr, cur_size,
			AV_NOPTS_VALUE, AV_NOPTS_VALUE, AV_NOPTS_VALUE);
		cur_ptr += len;
		cur_size -= len;
		if (packet.size == 0)
			continue;
		//Some Info from AVCodecParserContext
		printf("Packet Size:%6d\t", packet.size);
		switch (pCodecParserCtx->pict_type)
		{
		case AV_PICTURE_TYPE_I: printf("Type: I\t"); break;
		case AV_PICTURE_TYPE_P: printf("Type: P\t"); break;
		case AV_PICTURE_TYPE_B: printf("Type: B\t"); break;
		default: printf("Type: Other\t"); break;
		}
		printf("Output Number:%4d\t", pCodecParserCtx->output_picture_number);
		printf("Offset:%8ld\n", pCodecParserCtx->cur_offset);
		ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
		if (ret < 0)
		{
			printf("Decode Error.(解码错误)\n");
		}
		if (got_picture)
		{
			width_out = pCodecCtx->width;
			height_out = pCodecCtx->height;
			y_size = width_out*height_out;
			//sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
			//	pFrameYUV->data, pFrameYUV->linesize);
			if (!yuvimg_out)
			{
				yuvimg_out = (uchar*)malloc(y_size * 3 / 2 * sizeof(uchar));
			}
			//memcpy(yuvimg_out, pFrame->data, y_size * 3 / 2);
			int pp = 0;
			for (int i = 0; i < height_out; i++)
			{
				memcpy(yuvimg_out + pp, pFrame->data[0] + i * pFrame->linesize[0], width_out);
				pp += width_out;
			}
			//U
			for (int i = 0; i < height_out / 2; i++)
			{
				memcpy(yuvimg_out + pp, pFrame->data[1] + i * pFrame->linesize[1], width_out / 2);
				pp += width_out / 2;
			}
			//V
			for (int i = 0; i < height_out / 2; i++)
			{
				memcpy(yuvimg_out + pp, pFrame->data[2] + i * pFrame->linesize[2], width_out / 2);
				pp += width_out / 2;
			}
			printf("Succeed to decode 1 frame!\n");
			if (first_time)
			{
				printf("\nCodec Full Name:%s\n", pCodecCtx->codec->long_name);
				printf("width:%d\nheight:%d\n\n", pCodecCtx->width, pCodecCtx->height);
				img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
				size = avpicture_get_size(AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height);
				out_buffer = (uint8_t *)av_malloc(size);
				avpicture_fill((AVPicture *)pFrameBGR, out_buffer, AV_PIX_FMT_BGR24, pCodecCtx->width, pCodecCtx->height); // allocator memory for BGR buffer  
				cout << "pCodecCtx->width = " << pCodecCtx->width << "\npCodecCtx->height = " << pCodecCtx->height << endl;
				if (pCvMat->empty())
				{
					pCvMat->create(cv::Size(pCodecCtx->width, pCodecCtx->height), CV_8UC3);
				}
				first_time = 0;
			}
			//width_out = pCodecCtx->width;
			//height_out = pCodecCtx->height;
			//y_size = width_out*height_out;
			////sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
			////	pFrameYUV->data, pFrameYUV->linesize);
			//if (!yuvimg_out)
			//{
			//	yuvimg_out = (uchar*)malloc(y_size * 3 / 2 * sizeof(uchar));
			//}
			//memcpy(yuvimg_out,pFrame->data,y_size*3/2);
			//printf("Succeed to decode 1 frame!\n");
			video_getimg(pCodecCtx, img_convert_ctx, pFrame, pCvMat);
			cout << "size = " << size << endl;
			if (!(*pCvMat).empty())
			{
				(*pCvMat).copyTo(img);
				//cv::cvtColor(img, img, CV_GRAY2BGR);
				//cv::cvtColor(img, img, CV_BGR2YUV_I420);
				//resize(img, img, cv::Size(320, 256));
				imshow("Test", img);
				//memcpy(yuvimg_out, img.data, y_size * 3 / 2);
				cvWaitKey(1);
			}
#if 0
			while (1) {
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, &packet);
				if (ret < 0) {
					printf("Decode Error.(解码错误)\n");
					return ret;
				}
				if (!got_picture)
					break;
				if (got_picture) {
					printf("Flush Decoder: Succeed to decode 1 frame!\n");


					fwrite(pFrameYUV->data[0], 1, y_size, fp_out);     //Y
					fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_out);   //U
					fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_out);   //V
				}
			}
#endif
		}
	}
}
void OneFrameDecode::decode_oneframe_init()
{

	pCvMat = new cv::Mat();
	memset(in_buffer, 0, sizeof(in_buffer));
	cur_size = 0;
	first_time = 1;
	//str = bufferread(str1, size_a);
	cur_ptr = (uchar*)malloc(sizeof(uchar)*MAX_VIDEO_BUFFER);
	cur_ptr_head = cur_ptr;
	out_len = 235;
	len = 1;
	numbers = 0;

	pCodecCtx = NULL;
	pCodecParserCtx = NULL;
	codec_id = AV_CODEC_ID_HEVC;
	pFrameBGR = av_frame_alloc(); //存储解码后转换的RGB数据  
	result_node2 = NULL;
	avcodec_register_all();

	pCodec = avcodec_find_decoder(codec_id);
	if (!pCodec) {
		printf("Codec not found\n");
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (!pCodecCtx) {
		printf("Could not allocate video codec context\n");
	}

	pCodecParserCtx = av_parser_init(codec_id);
	if (!pCodecParserCtx) {
		printf("Could not allocate video parser context\n");
	}

	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
		printf("Could not open codec\n");
	}
	pFrame = av_frame_alloc();
	av_init_packet(&packet);
}
void OneFrameDecode::decode_oneframe_delete()
{

	//Flush Decoder
	packet.data = NULL;
	packet.size = 0;

	//	fclose(fp_in);
	//	fclose(fp_out);
	delete pCvMat;
	delete video_bufglobal;
	if (cur_ptr_head)
	{
		free(cur_ptr_head);
	}
	if (yuvimg_out)
	{
		free(yuvimg_out);
	}
	img_convert_ctx = NULL;
	av_parser_close(pCodecParserCtx);

	//av_frame_free(&pFrameYUV);
	av_frame_free(&pFrameBGR);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	av_free(pCodecCtx);

}
DLL_API void imgprocess(uchar *pInData, int iInDataLen, int &iOutWidth, int &iOutHeight, uchar * pOutData)
{

	video_bufglobal = decode1.img_unpack(pInData, iInDataLen);
	//video_bufglobal = pInData;
	if (isFirstPack == 1)
	{
		if (isLastPack == 1)
		{
			decode1.decode_oneframe_delete();
			isLastPack = 0;
		}
		decode1.decode_oneframe_init();
		isFirstPack = 0;
	}
	decode1.decode_oneframe(video_bufglobal, iInDataLen - 8);
	iOutWidth = width_out;
	iOutHeight = height_out;
	memcpy(pOutData, yuvimg_out, width_out*height_out * 3 / 2);
}