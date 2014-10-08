/*
 * sim.h
 *
 *  Created on: May 5, 2014
 *      Author: david ahmadi
 */

#ifndef SIM_H
#define SIM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//struct has valid, dirty, and tag for each line in cache
typedef struct node {
	char vb;
	char db;
	unsigned int tag;
} line;

//convert hex to binary
unsigned int hextoBin(char *ptr);

#endif
