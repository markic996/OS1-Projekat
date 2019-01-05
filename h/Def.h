/*
 * Def.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef DEF_H_
#define DEF_H_


#include "idle.h"

extern volatile unsigned required_switch;
extern volatile unsigned int lock_flag;
extern volatile int counter;

#define _LOCK asm { pushf; cli; }
#define _UNLOCK asm { popf; }

extern int counterIdle;
extern volatile unsigned over;

#define lock lock_flag=0
#define unlock  {lock_flag=1 ; if(required_switch)dispatch();}

extern Idle* idlethr;
extern volatile unsigned flagidle;
extern PCB* idlepcb1;


#endif /* DEF_H_ */
