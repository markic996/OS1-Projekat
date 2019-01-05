/*
 * Def.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "Def.h"
#include "Thread.h"
#include "idle.h"


volatile unsigned int lock_flag=1;
volatile unsigned required_switch=0;
volatile unsigned flagidle=1;
volatile int counter=20;

int counterIdle=0;
volatile unsigned over=0;

Idle* idlethr=0;
PCB* idlepcb1=0;



