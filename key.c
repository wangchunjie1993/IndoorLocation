#include<avr/io.h>
#include<util/delay.h>
#include"def.h"

//PA0-PA3,PA7-PA4


uchar key_press()
{
   uchar i;
DDRA=0XFF;
PORTA=0XF0;

DDRA=0X0F;
i=PINA;
if(i==0xf0)
{
   DDRA=0XFF;
   return 0;
  
}
else
{
   DDRA=0XFF;
   return 1;
}
}
uchar key_scan()
{
    uchar key,i=0x7f,j,code;
   _delay_ms(10);
   if(key_press())
   {
      do
    {
     i=(i<<1|i>>7);
     PORTA=i;
     DDRA=0X0F;
     key=PINA;
     j=key&0xf0;
    
    }while(j==0xf0);
   
    while(key_press());
    _delay_ms(10);
    switch(key)
    {
    case 0x7e: code=0;break;
     case 0xbe: code=1;break;
     case 0xde: code=2;break;
     case 0xee: code=3;break;
    
     case 0x7d: code=4;break;
     case 0xbd: code=5;break;
     case 0xdd: code=6;break;
     case 0xed: code=7;break;
    
     case 0x7b: code=8;break;
     case 0xbb: code=9;break;
     case 0xdb: code=10;break;
     case 0xeb: code=11;break;
    
     case 0x77: code=12;break;
     case 0xb7: code=13;break;
     case 0xd7: code=14;break;
     case 0xe7: code=15;break;
     
	 default: return 0xff;break;
    }
   }
   
return code;
}
