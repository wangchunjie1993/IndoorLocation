#include"2401.h"
#include"SPI.h"



unsigned char TxData[TRAN_DATA_NUM]={};	//Ҫ���͵�����
unsigned char RxData[TRAN_DATA_NUM]={};	//Ҫ���յ�����
unsigned char TxAdd[TxAddNum]={0XE7,0XE7,0XE7,0XE7,0XE7};

///*********************
//2401��ʼ��
///*********************
void RF2401_Init(void)
{
    SPI_Init();
	DDR_SPI|=((1<<MOSI)|(1<<SCK)|(1<<CSN));	//����MOSI��SCK��CSN�������������
	DDRF|=(1<<CE);
	DDR_SPI&=~(1<<MISO);//|(1<<IRQ));	
	DDRF &= ~(1<<IRQ);
	PORTF |=(1<<IRQ);
	PORT_SPI|=(1<<CSN);
}

void set_tx_mode()
{
    Sleep1_Mode();

	PORT_SPI&=~(1<<CSN);
	SpiRW(1|W_REGSITER);	//д �Ĵ���1
	SpiRW(0x0);				//��ֹ�Զ�Ӧ��  
	PORT_SPI|=(1<<CSN);

	PORT_SPI&=~(1<<CSN);   
	SpiRW(0x31);			
	SpiRW(0X20);			//ͨ��0��Ч���ݿ��32
	PORT_SPI|=(1<<CSN);
	_delay_ms(1);
    Tx_Mode();
}

void send_data()
{
 //unsigned char i;
 //for(i=0;i<32;i++)			//���ͽ��յ�������
  //TxData[i]=i;//RxData[i];
 W_Send_Data(32);
 Tx_Mode();
}

void set_rx_mode()
{
 Sleep1_Mode();

 PORT_SPI&=~(1<<CSN);
 SpiRW(1|W_REGSITER);	//д �Ĵ���1
 SpiRW(0x0);				//��ֹ�Զ�Ӧ��
 PORT_SPI|=(1<<CSN);

 PORTB&=~(1<<CSN);   
 SpiRW(0x31);			
 SpiRW(0X20);			//ͨ��0��Ч���ݿ��32
 PORTB|=(1<<CSN);
 _delay_ms(1);
 Rx_Mode();//����ģʽ
}

void receive_data()
{
 unsigned char irq_sta;
 while((PINF&(1<<IRQ)));

 do
 {  
  irq_sta=Read_IRQ();
 }while(!(irq_sta&(1<<RX_DR)));

 Clr_IRQ(1<<RX_DR);
 Read_Rx(32);
 _delay_ms(1);

}

///*********************
//����ģʽ
///*********************
void Tx_Mode(void)
{
	PORTF&=~(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);			//д�Ĵ��� 0
	SpiRW(0x12);		//ʹ�������жϣ�crcʹ�ܣ�8λcrc���ϵ磬����ģʽ
	PORT_SPI|=(1<<CSN);
	PORTF|=(1<<CE);
	_delay_ms(1);
}
///*********************
//����ģʽ
///*********************
void Rx_Mode(void)
{
	PORTF|=(1<<CE);
	PORT_SPI&=~(1<<CSN);
	SpiRW(0|W_REGSITER);			//д�Ĵ��� 0
	SpiRW(0x13);		//ʹ�������жϣ�crcʹ�ܣ�8λcrc���ϵ磬	����ģʽ
	PORT_SPI|=(1<<CSN);
	_delay_ms(2);
}
///*********************
//����1ģʽ
///*********************
void Sleep1_Mode(void)
{
	PORTF&=~(1<<CE);
}
///*********************
//д Ҫ���͵���Ч����
///*********************
void W_Send_Data(unsigned char send_data_num)
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_TX);	//���TX fifo�Ĵ���
	PORT_SPI|=(1<<CSN);
	PORT_SPI&=~(1<<CSN);
	SpiRW(W_TX_PAYLOAD);//д����
	unsigned char i;
	for(i=0;i<send_data_num;i++)
	{
		SpiRW(TxData[i]);
	}
	PORT_SPI|=(1<<CSN);
}
///*********************
//�� ���յ�����Ч����
///*********************
void Read_Rx(unsigned char rece_data_num)//����Ҫ��ȡ��������Ŀ
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(R_RX_PAYLOAD);//������	RX FIFO
	unsigned char i;
	for(i=0;i<rece_data_num;i++)
	{
		RxData[i]=SpiRW(NOP);
	}
	PORT_SPI|=(1<<CSN);

	PORT_SPI&=~(1<<CSN);
	SpiRW(FLUSH_RX);	//���RX 	fifo�Ĵ���
	PORT_SPI|=(1<<CSN);
}
///*********************
//�� �жϱ�־
///*********************
unsigned char Read_IRQ(void)
{
	PORT_SPI&=~(1<<CSN);
	unsigned char sta;
	sta=SpiRW(0X07);					//��״̬�Ĵ���	��NOP����Ҳ�ɽ�״̬����
	PORT_SPI|=(1<<CSN);
	return sta;
}
///*********************
//�����־λ
///*********************
void Clr_IRQ(unsigned char note)	//ʾ����Cle_IRQ(((1<<tx_dr)|(1<<max_rt)))
{
	PORT_SPI&=~(1<<CSN);
	SpiRW(0X07|W_REGSITER);		//д״̬�Ĵ���
	SpiRW(note);
	PORT_SPI|=(1<<CSN);
}
