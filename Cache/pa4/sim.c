/*
 * sim.c
 *
 *  Created on: May 5, 2014
 *      Author: david ahmadi
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sim.h"

int main(int argc, char** argv) {
	unsigned int cacheHit, cacheMiss, memoryRead, memoryWrite, memoryAddress, index, tagVal;
	int current;
	char policy;
	char readOrWrite;
	unsigned short cacheSize;
	char *buffer;
	int count = 0;
	cacheHit = 0;
	cacheMiss = 0;
	memoryRead = 0;
	memoryWrite = 0;
	cacheSize = 4096;
	line cache[4096];
	FILE *fp;

	for (current = 0; current < cacheSize; current++) {
		cache[current].vb = '0';
		cache[current].db = '0';
	}

	if (argc <= 1 || argc > 3) {
		printf("Error: Input is Not Allowed\n");
		return 1;
	}

	if (strcmp("-h", argv[1]) == 0) {
		printf("Usage: sim <write policy> <trace file>\n");
		return 0;
	}
	//check write policy
	if ((strcmp("wt", argv[1]) != 0) && (strcmp("wb", argv[1]) != 0)) {
		printf("Error: Write Policy is Not Allowed\n");
		return 1;
	}
	//set policy write through / back
	if (strcmp("wt", argv[1]) == 0)
		policy = 't';
	else
		policy = 'b';

	//trace file
	fp = fopen(argv[2], "r");
	if (fp == NULL) {
		printf("Trace file not found. Please run again.\n");
		return 1;
	}

	index = 0;
	tagVal = 0;
	buffer = malloc(1024);
	memoryAddress = 0;
	//Iterate over each line
	while(buffer[0] != '#' && fgets(buffer, 1024, fp) != NULL){
		readOrWrite = strstr(buffer, "W") == NULL ? 'r' : 'w';
		memoryAddress = hextoBin(buffer) / 4;
		index = memoryAddress % cacheSize;
		tagVal = memoryAddress / cacheSize;

		//write through
		if (policy == 't'){
			count++;
			if (cache[index].vb == '0'){
				cacheMiss++;
				memoryRead++;
				cache[index].tag = tagVal;
				cache[index].vb = '1';
			}else{
				if (tagVal == cache[index].tag)
					cacheHit++;
				else{
					cacheMiss++;
					memoryRead++;
					cache[index].tag = tagVal;
				}
			}
			if (readOrWrite == 'w'){
				memoryWrite++;
				count--;
			}
		}else{
			if (cache[index].vb == '0'){
				cacheMiss++;
				memoryRead++;
				cache[index].tag = tagVal;
				cache[index].vb = '1';
			}else{
				if (cache[index].tag == tagVal)
					cacheHit++;
				else{
					if (cache[index].db == '1')
						memoryWrite++;

					cache[index].tag = tagVal;
					cache[index].db = '0';
					cacheMiss++;
					memoryRead++;
				}
			}
			if (readOrWrite == 'w')
				cache[index].db = '1';
		}
	}

	printf("%s%u\n", "Cache Hits: ", cacheHit);
	printf("%s%u\n", "Cache Misses: ", cacheMiss);
	printf("%s%u\n", "Memory Reads: ", memoryRead);
	printf("%s%u\n", "Memory Writes: ", memoryWrite);

	fclose(fp);
	free(buffer);
	return 0;
}
//convert hex to binary
unsigned int hextoBin(char *pointer) {
	unsigned int value;
	int i;
	int ord;
	value = 0;
	ord = strlen(pointer) - 2;
	for (i = ord; pointer[i] != 'x'; i--)
		value += (pointer[i] <= '9' ? pointer[i] - '0' : pointer[i] - 'a' + 10) << ((ord - i) * 4);
	return value;
}
