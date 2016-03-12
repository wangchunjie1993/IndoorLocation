#include"def.h"

#ifndef __MOTOR_H__
#define __MOTOR_H__

void motor_init();
void forward();
void forward_count(int counter);
void left();
void left_count(int counter);
void right();
void right_count(int counter);
void backward();
void backward_count(int counter);
void motor_stop();

#endif
