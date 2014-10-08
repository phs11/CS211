/*
 * wordstat.c
 *
 *  Created on: Feb 25, 2014
 *      Author: david ahmadi
 */
#include <stdio.h>
#define BUFFER_SIZE 1000
#include <string.h>
#define WORD_LEN 100
#include <ctype.h>
#include <stdlib.h>

//Initialize structure
 struct Node{
    int occurrence;
    int caseOcc;
    char *str;
    struct Node *left;
    struct Node *right;
    struct linkedList *next;
    };
    struct linkedList{
    char *str;
    struct linkedList *next;
    };
//Prints output of structure and lists strings with number of occurrences
void printResult(struct Node * root){
    if (root == NULL)
        return;
    printResult(root->left);
    for(int i = 0; root->str[i]; i++){
      root->str[i] = tolower(root->str[i]);
    }
    printf("%s \t \t %d \t \t \t %d \n", root->str, root->occurrence, root->caseOcc);
    printResult(root->right);
}

// This function will take the word and store it in proper data structures
void processStr(struct Node** root, char * a) {

    if (*root == NULL) {
        struct Node * node = (struct Node *) malloc(sizeof(struct Node));
        node->str = (char*) malloc(sizeof(char));
        strcpy(node->str, a);
        node->occurrence = 1;
        node->caseOcc = 1;
        node->left = NULL;
        node->right = NULL;
        node->next = NULL;
        *root = node;
    }
    else {
    int casecomp = strcasecmp((*root)->str, a);
        if(casecomp < 0)
        	processStr(&(*root)->right, a);
        if(casecomp > 0)
        	processStr(&(*root)->left, a);
        if(casecomp == 0) {
            (*root)->occurrence++; /*Increments occurrences*/

            struct linkedList *next = (struct linkedList*)malloc(sizeof(struct linkedList*));
            next = NULL;
            (*root)->next = next;
        }
    }
}

int main()
{
    struct Node * tree = NULL;
    FILE *input;
    char buffer [BUFFER_SIZE];
    input = fopen("test1.txt", "r");	//takes test1 as file input
    char *token;

//checks strings for symbols
    if (input != NULL) {
        while (fgets(buffer, sizeof(buffer)/sizeof(char), input)){
            token = strtok(buffer, ",./<>?`~!@#$%^&*()_-+=:;\"\'\\| []{}");
            while (token) {
            	processStr(&tree, token);
                token = strtok(NULL, ",./<>?`~!@#$%^&*()_-+=:;\"\'\\| []{}");
            }
        }

    fclose(input);
    printf("%s \n", "Word \t Total No. of Occurrences \t No. Case-Sensitive Versions\n");
    printResult(tree);
    }
//End
    else
        printf("%s", "File not found, incorrect input");
}
