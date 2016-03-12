#ifndef _SPI_H_
#define _SPI_H_
///SPI�궨��
#include<avr/io.h>
#define DDR_SPI		DDRB
#define PORT_SPI	PORTB
#define CSN 		PB0	//�źŵ�Ƭѡ���͵�ƽоƬ����
#define MOSI 		PB2//Master Output Slave Input
#define MISO 		PB3//Master Input Slave Output
#define SCK 		PB1//ʱ���ź�
#define CE			PF2//оƬģʽ������
#define IRQ			PF3//�ж��ź�

void SPI_Init(void);
uint8_t SpiRW(uint8_t val);
#endif
