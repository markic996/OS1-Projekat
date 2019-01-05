/*
 * listsem.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_


#include "Def.h"
#include "semaphor.h"

class KernelSem;

class ListSem{
	struct Elem{
		KernelSem* p;
		Elem* next;
		Elem(KernelSem* pp,Elem* s=0){
			p=pp;
			next=s;
		}
	};
	Elem* first,*last;

public:

	ListSem(){
		first=last=0;
	}
    ~ListSem();
	void addsem(KernelSem* p);
	void removesem(KernelSem* p);
	void FindTimeOver();
};



#endif /* LISTSEM_H_ */
