#include<avr/io.h>
#include"SPI.h"
#include"def.h"
//SPI��ʼ��
void SPI_Init(void)
{
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN));	//����MOSI��SCK��CSN�������������
	DDRF|=(1<<CE);
	DDR_SPI&=~(1<<MISO);					//һֱΪ����ģʽ
	DDRF &= ~(1<<IRQ);
    PORTF |= (1<<IRQ);
	SPCR|=((1<<SPE)|(1<<MSTR));						//ʹ��SPI��������set clock rate fck/4
													//
}


// SPI������д����
uint8_t SpiRW(uint8_t val)  	
{
	uint8_t temp; 
    SPDR=val; 
	while (!(SPSR&(1<<SPIF)))
		; 
    temp=SPSR;//��SPIF����
	temp=SPDR; 
    return temp; 
} 
