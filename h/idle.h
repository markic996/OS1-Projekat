/*
 * idle.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_


#include "Thread.h"

class Idle:Thread{

public:
	Idle();
    ~Idle();
    void start();
	virtual void run();

	PCB* idlepcb;
};

#endif /* IDLE_H_ */
