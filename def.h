#include<avr/io.h>

#ifndef __DEF_H__
#define __DEF_H__

#define uchar unsigned char
#define uint unsigned int

typedef union
{
 uint data_use;
 uchar data_trans[2];
}Int_U;

#endif
