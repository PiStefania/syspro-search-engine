#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invertedIndex.h"
#include "dfQuery.h"

int retDocFrequency(rootNode* root,char* word){
	if(root == NULL){
		return -1;
	}
	
	if(root->start == NULL){
		return -1;
	}
	
	trieNode* tempNode = root->start->firstNode;
	for(int i=0; i< strlen(word); i++){
		while(tempNode != NULL){
			if(tempNode->character == word[i]){
				if(i != strlen(word)-1){
					tempNode = tempNode->head->firstNode;
					break;
				}else{
					return tempNode->documentFrequency;
				}
			}else{
				tempNode = tempNode->nextNode;
			}
		}
		if(tempNode == NULL){
			return -2;
		}
	}
}

void BFS(trieNode* node,stack* stackWord){
	if (node != NULL){
		if (node->nextNode != NULL){
			BFS(node->nextNode,stackWord);
		}
		
		if (node->head->firstNode != NULL){
			BFS(node->head->firstNode,stackWord);
		}
		
		
		stackNode* pushNode = malloc(sizeof(stackNode));
		pushNode->alternatives = node->head->size;
		pushNode->character = node->character;
		pushNode->docFrequency = node->documentFrequency;
		if(node->postList != NULL){
			pushNode->lastChar = 1;
		}else{
			pushNode->lastChar = 0;
		}
		stackPush(stackWord,pushNode);
		
		if(node->firstChar){
			//end of word
			int docFrequency = 0;
			
			printStack(stackWord);
			int counterUp = 0;
			int lastFlag = 0;
			int alternatives = 0;
			while(!stackIsEmpty(stackWord)){
				stackNode* tempNode = stackPop(stackWord);
				if(tempNode == NULL){
					break;
				}else if(tempNode->alternatives < 0){
					//last char 
					docFrequency = tempNode->docFrequency;
					printf("%c %d\n",tempNode->character,docFrequency);
					stackWord->top += counterUp;
					lastFlag = 1;
					alternatives--;
					break;
				}else if(tempNode->alternatives == 0){
					//has next char
					if(lastFlag){
						counterUp++;
						stackWord->top -= counterUp;
						lastFlag = 0;
						counterUp = 0;
					}
					printf("%c",tempNode->character);
					if(alternatives != 0){
						counterUp++;
					}
				}else{
					//has more alternatives
					alternatives = tempNode->alternatives;
					printf("%c",tempNode->character);				
				}
			}
		}
	}
}


//stack's functions
void initializeStack(stack** stackWord,int size){
	(*stackWord)->elements = malloc(size*sizeof(stackNode));
	(*stackWord)->top = -1;
	(*stackWord)->size = size;
}

void destroyStack(stack** stackWord){
	free((*stackWord)->elements);
	(*stackWord)->elements = NULL;
	(*stackWord)->size = 0;
	(*stackWord)->top = -1;
	free(*stackWord);
	*stackWord = NULL;
}

int stackIsEmpty(stack* stackWord){
	return (stackWord->top < 0);
}

int stackIsFull(stack* stackWord){
	return (stackWord->top >= (stackWord->size - 1));
}

void doubleStack(stack* stackWord){
	int oldSize = stackWord->size;
	stackWord->elements = realloc(stackWord->elements,2*oldSize*sizeof(stackNode));
	stackWord->size = 2*oldSize;
}

void stackPush(stack* stackWord,stackNode* node){
	if(stackIsFull(stackWord)){
		doubleStack(stackWord);
	}
	
	stackWord->top++;
	stackWord->elements[stackWord->top] = *node;
}

stackNode* stackPop(stack* stackWord){	
	if(!stackIsEmpty(stackWord)){
		if(stackWord->elements[stackWord->top].alternatives <= 1){
			stackWord->elements[stackWord->top].alternatives--;
			stackNode* elem = &stackWord->elements[stackWord->top];
			stackWord->top--;
			return elem;
		}
		else{
			stackWord->elements[stackWord->top].alternatives--;
			stackNode* elem = &stackWord->elements[stackWord->top];
			return elem;
		}
	}
	return NULL;
}

void printStack(stack* stackWord){
	for(int i=stackWord->top;i>=0;i--){
		printf("%dth Elem: %c\n",i,stackWord->elements[i].character);
	}
}
