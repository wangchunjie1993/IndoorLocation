#include<avr/io.h>
#include"def.h"

//PB4输出CTC,PB6、PB7控制电机方向

int motor_CTC_counter;

void motor_init()
{
 TCCR0=0x00;
 TCNT0=0x00;
 OCR0=0xcc;
 TCCR0|=(7<<2);
}

void forward()
{
 PORTB&=~((1<<6)|(1<<7));
 PORTB|=(1<<6);
 DDRB|=(1<<4);
}

void forward_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB&=~((1<<6)|(1<<7));
 PORTB|=(1<<6);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void left()
{
 PORTB|=(1<<6)|(1<<7);
 DDRB|=(1<<4);
}

void left_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB=(1<<6)|(1<<7);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void right()
{
 PORTB&=~((1<<6)|(1<<7));
 DDRB|=(1<<4);
}

void right_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB&=~((1<<6)|(1<<7));
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void backward()
{
 PORTB&=~((1<<6)|(1<<7));
 PORTB|=(1<<7);
 DDRB|=(1<<4);
}

void backward_count(int counter)
{
 motor_CTC_counter=counter;
 PORTB&=~((1<<6)|(1<<7));
 PORTB|=(1<<7);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 while(motor_CTC_counter>=0);
 motor_stop();
 TIMSK&=~(1<<1);
}

void motor_stop()
{
	DDRB&=~(1<<4);
}




