#include<avr/io.h>
#include"def.h"


#ifndef __SPI_H__
#define __SPI_H__

void SPI_master_init();
uchar SPI_master_transmit(uchar data);
void SPI_slave_init();
uchar SPI_slave_receive();

#endif
