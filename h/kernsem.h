/*
 * kernsem.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_


#include "semaphor.h"
#include "list.h"
#include "listsem.h"

class Semaphore;

class List;

extern ListSem* semaphores;

class KernelSem{

public:

	List* Blocked;

	KernelSem (int init,Semaphore* sem);

    virtual ~KernelSem ();
    virtual int wait (Time maxTimeToWait);
    virtual void signal();

	int val ();

protected:

	void block(Time mt);
	void deblock();

private:

	int value;
	Semaphore* mySem;

};




#endif /* KERNSEM_H_ */
