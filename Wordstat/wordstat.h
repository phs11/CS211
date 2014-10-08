/*
 * wordstat.h
 *
 *  Created on: Feb 28, 2014
 *      Author: david ahmadi
 */

#ifndef WORDSTAT_H_
#define WORDSTAT_H_
//--
struct BST{
    char* word;
    int numOccur;
    int numCaseOccur;
    struct BST* left;
    struct BST* right;
};

struct BST* search(struct BST* root, char* data);
struct BST* new_node(char* data);
void insert(struct BST** root, char* data);
//---
#endif /* WORDSTAT_H_ */
