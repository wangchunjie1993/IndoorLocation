#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"usart.h"
#include"def.h"

uchar start_arr[9]={0x55,0xaa,0xa0,0x10,0x03,0x03,0x11,0x14,0xd7};			//无线定位模块启动数组
uchar start_ok_arr[8]={0x55,0xaa,0x10,0xa0,0x02,0x03,0x00,0xfc};			//无线定位模块启动校验数组
uchar wireless_receive_arr[29]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};		//无线定位模块接收数据数组

Int_U x1,x2,y1,y2,x,y;								

uchar wireless_receive_counter=0;		//无线定位模块接收数据计数
uchar start_ok_flag=0;			//无线定位模块启动成功标志


//启动无线定位模块
void start_wireless()
{
 uchar i;

 do
 {
  for(i=0;i<9;i++)
  {
   usart1_transmit(start_arr[i]);
   _delay_us(10);
  }

  wireless_receive_counter=0;
  UCSR1B|=(1<<7);		//打开串口接收中断
  while(wireless_receive_counter<8);
  UCSR1B&=~(1<<7);		//关闭串口接收中断

  start_ok_flag=1;
  for(i=0;i<8;i++)
  {
   if(start_ok_arr[i]!=wireless_receive_arr[i])
   {
    start_ok_flag=0;
    break;
   }
  }
 }while(start_ok_flag==0);
 
}


//读取超声波定位模块返回坐标值
uchar read_wireless_sensor()
{
 uchar i;
 uchar ok_flag=0;
 
 wireless_receive_counter=0;
 UCSR1B|=(1<<7);		//打开串口接收中断
 while(wireless_receive_counter<29);
 UCSR1B&=~(1<<7);		//关闭串口接收中断

 for(i=0;i<29;i++)
 {
  if((wireless_receive_arr[i]==0x55)&&(wireless_receive_arr[i+1]==0xaa))
  {
   ok_flag=1;
   break;
  }
 }
 if(ok_flag==0)
 return 0;
 
 i+=6;
 x1.data_trans[0]=wireless_receive_arr[i++];
 x1.data_trans[1]=wireless_receive_arr[i++];
 y1.data_trans[0]=wireless_receive_arr[i++];
 y1.data_trans[1]=wireless_receive_arr[i++];
 
 x2.data_trans[0]=wireless_receive_arr[i++];
 x2.data_trans[1]=wireless_receive_arr[i++];
 y2.data_trans[0]=wireless_receive_arr[i++];
 y2.data_trans[1]=wireless_receive_arr[i];
 
 x.data_use=(x1.data_use+x2.data_use)/2;
 y.data_use=(y1.data_use+y2.data_use)/2;
 
 return 1;
}

