/*******************************************************
 * @作者: 黄竞辉
 * @Date: 2020-10-08 02:05:15
 * @LastEditTime: 2020-10-08 03:16:19
 * @最后编写者: 黄竞辉
 * @描述: 
 * @FilePath: /Harb_Device/device/inc/Deque_Buffer.h
 * @评论备注: 
 *******************************************************/
#ifndef DEQUE_BUFFER_H
#define DEQUE_BUFFER_H

#include "common.h"
#include <deque>
#include <mutex>
#define MAXCHAINDEQUESIZE	10000
class Deque_Buffer
{
public:
	void Init_buffer();
	std::deque<uint8_t *> dequeBuffEmpty;
	std::deque<uint8_t *> dequeBuffUse;
	std::mutex dequeBuffEmptyMutex;
	std::mutex dequeBuffUseMutex;
	uint8_t * popFrontFrom_dequeBuffEmpty();
	void pushBackTo_dequeBuffEmpty(uint8_t *);
	uint8_t * popFrontFrom_dequeBuffUse();
	void pushBackTo_dequeBuffUse(uint8_t *);
};


#endif