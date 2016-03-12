#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"def.h"
#include"wireless.h"
#include"usart.h"
#include"motor.h"
#include"2401.h"
#include"LCD12864Driver_IO.h"
#include"LCD12864User.h"
#include"ISD1700.h"
#include"key.h"

Int_U X_dest,Y_dest;	//目标位置坐标
uchar key_val;

extern unsigned char TxData[TRAN_DATA_NUM];	//要发送的数据

int main()
{
 //usart0_init(25);
 //usart1_init(25);	//19200	
 lcd_display_initialize();
 RF2401_Init();
 ISD_Init();
 //motor_init();
 SREG=0x80;
// start_wireless();

 display_yanshan_image();
 while(1)
 {
  display_start_image();
  set_point();
  set_tx_mode();

  TxData[0]=X_dest.data_trans[0];
  TxData[1]=X_dest.data_trans[1];
  TxData[2]=Y_dest.data_trans[0];
  TxData[3]=Y_dest.data_trans[1];

  send_data();
 }

}

void display_X()
{
 lcd_command_write(0x30);	//基本指令集
 
 lcd_command_write(0x89);
 lcd_data_write(X_dest.data_use/1000+48);
 lcd_data_write(X_dest.data_use%1000/100+48);
 lcd_data_write(X_dest.data_use%100/10+48);
 lcd_data_write(X_dest.data_use%10+48);
}

void display_Y()
{
 lcd_command_write(0x30);	//基本指令集
 
 lcd_command_write(0x99);
 lcd_data_write(Y_dest.data_use/1000+48);
 lcd_data_write(Y_dest.data_use%1000/100+48);
 lcd_data_write(Y_dest.data_use%100/10+48);
 lcd_data_write(Y_dest.data_use%10+48);
}

void display_yanshan_image()
{
 lcd_picture_draw(gImage_yanshan);
 SetPlay(0);
 do{
  while(key_press()==0x00);
 }while((key_val=key_scan())!=12);
}

void display_start_image()
{
 lcd_screen_clear();
 _lcd_picture_clear();
 lcd_string_write(0x80,"超声波定位系统");
 lcd_string_write(0x90,"请输入目的坐标：");
 lcd_string_write(0x88,"X=0000mm");
 lcd_string_write(0x98,"Y=0000mm");
}

void set_point()
{
 char weishu=3;
 X_dest.data_use=Y_dest.data_use=0;
 
 while(key_press()==0);
 key_val=key_scan();
 while(key_val!=12)			//设置X坐标
 {
  if((key_val!=3)&&(key_val!=7)&&(key_val!=11)&&(key_val!=14)&&(key_val!=15))
  {
   if((key_val>=0)&&(key_val<=2)){key_val++;}
   else if((key_val>=8)&&(key_val<=10)){key_val--;}
   else if(key_val==13){key_val=0;}
   if(weishu==3)
   {
    X_dest.data_use+=key_val*1000;
	weishu--;
	display_X();
   }
   else if(weishu==2)
   {
    X_dest.data_use+=key_val*100;
	weishu--;
	display_X();
   }
   else if(weishu==1)
   {
    X_dest.data_use+=key_val*10;
	weishu--;
	display_X();
   }
   else if(weishu==0)
   {
    X_dest.data_use+=key_val;
	display_X();
	weishu--;
   }
  }
  
  while(key_press()==0);
  key_val=key_scan();
  
 }
 

 weishu=3;
 while(key_press()==0);
 key_val=key_scan();
 while(key_val!=12)			//设置Y坐标
 {
  if((key_val!=3)&&(key_val!=7)&&(key_val!=11)&&(key_val!=14)&&(key_val!=15))
  {
   if((key_val>=0)&&(key_val<=2)){key_val++;}
   else if((key_val>=8)&&(key_val<=10)){key_val--;}
   else if(key_val==13){key_val=0;}
   if(weishu==3)
   {
    Y_dest.data_use+=key_val*1000;
	weishu--;
	display_Y();
   }
   else if(weishu==2)
   {
    Y_dest.data_use+=key_val*100;
	weishu--;
	display_Y();
   }
   else if(weishu==1)
   {
    Y_dest.data_use+=key_val*10;
	weishu--;
	display_Y();
   }
   else if(weishu==0)
   {
    Y_dest.data_use+=key_val;
	display_Y();
	weishu--;
   }
  }
  
  while(key_press()==0);
  key_val=key_scan();
  
 }
}

