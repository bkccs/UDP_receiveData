#ifndef DATACHAIN_H
#define DATACHAIN_H

#include "common.h"

typedef struct
{
    uint8_t HEADFLAG[2];
    uint8_t DataLength;
    uint8_t ID_SRC;
    uint8_t ID_DATA;
    MyU16 NUMB;
    uint8_t data[235];
    uint8_t crc;
}DataChainCommonType;


#define u8float(data)   (*((float *)data))
#define u8double(data)   (*((double *)data))
#define u8short(data)   (*((short *)data))
#define u8long(data)   (*((long *)data))
#define u8u16(data)   (*((uint16_t *)data))
#define u8u32(data)   (*((uint32_t *)data))
#define u8u64(data)   (*((uint64_t *)data))

#endif // DATACHAIN_H
