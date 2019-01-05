/*
 * list.h
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_


#include "Def.h"
#include "kernel.h"

class PCB;

class List{
	struct Elem{
		PCB* p;
		Elem* next;
		Elem(PCB* pp,Elem* s=0){
			p=pp;
			next=s;
		}
		~Elem(){
			next=0;p=0;
		}
	};
	Elem* first,*last;

public:
	List(){
		first=last=0;
	}
	List(PCB* p);
    ~List(){
    	remove();
    }

	void remove();
	void addpcb(PCB* p);
	void overWait();
	void FindTO();
	void deblock(PCB* p);
	void removebyID(ID i);
	PCB* findpcb(ID i);
	PCB* getFirst();
};

extern List* threads;


#endif /* LIST_H_ */
