#ifndef _2401_H_
#define _2401_H_
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
///***************************
///***************************
//2401���������� 
///***************************
//���������
#define R_REGSITER	  0X00	//���Ĵ���	ֱ�����ַ��λ��
#define W_REGSITER	  0X20	//д�Ĵ���	ֱ�����ַ��λ��,ֻ���ڵ���ģʽ�����ģʽ�²���
#define R_RX_PAYLOAD  0X61	//������ 1-32 �ֽ�  ��0�ֽڿ�ʼ�����ڽ���ģʽ��
#define W_TX_PAYLOAD  0XA0	//д���� 1-32 �ֽ�  ��0�ֽڿ�ʼ�����ڷ���ģʽ��
#define FLUSH_TX	  0xe1	//���TX FIFO �Ĵ��������ڽ���ģʽ��
#define FLUSH_RX      0XE2	//���RX FIFO �Ĵ��������ڷ���ģʽ�£� ����Ӧ���ź�ʱ����Ӧʹ�ô�����
#define RESUSE_TX_PL  0XE3	//Ӧ���ڷ���ˣ�����ʹ����һ����Ч���ݣ���CEΪ��ʱ�����ݰ��������·���
#define NOP			  0XFF	//��ָ�� ����ȡ������

//״̬�Ĵ����б�־λ
#define RX_DR	6	//�����ж�
#define	TX_DS	5	//��������ж�
#define MAX_RT	4	//����ط��ж�

#define RECE_DATA_NUM	32	//�������������
#define TRAN_DATA_NUM	32	//�������������
#define TxAddNum		5	//���͵�ַ���
#define RxAddNum		5	//���͵�ַ���

/*******24L01��ʼ��*********/
void RF2401_Init(void);
/*******����ģʽ**********/
void Tx_Mode(void);
/*******����ģʽ**********/
void Rx_Mode(void);
/*******����ģʽһ********/
void Sleep1_Mode(void);
/*******д Ҫ���͵���Ч����**********/
void W_Send_Data(unsigned char send_data_num);//����Ҫ��ȡ��������Ŀ
/*******�� ���յ�����Ч����**********/
void Read_Rx(unsigned char rece_data_num);//����Ҫ��ȡ��������Ŀ
/*******�� �жϱ�־********/
unsigned char Read_IRQ(void);
/*******�����־λ**********/
void Clr_IRQ(unsigned char note);

#endif
