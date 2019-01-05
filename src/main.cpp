/*
 * main.cpp
 *
 *  Created on: Aug 30, 2017
 *      Author: OS1
 */

#include "timer.h"


extern int userMain (int argc, char* argv[]);

int retvalue;

int main(int argc, char* argv[]){
	init();
	retvalue = userMain(argc, argv);
	restore();
	return retvalue;
}



