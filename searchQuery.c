#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchQuery.h"
#define K1 1.2
#define B 0.75

void initializeGeneralInfo(generalInfo** info){
	*info = malloc(sizeof(generalInfo));
	(*info)->totalWords = 0;
	(*info)->totalDocuments = 0;
	(*info)->k1 = K1;
	(*info)->b = B;
}

void destroyGeneralInfo(generalInfo** info){
	free(*info);
	*info = NULL;
}

void getScoreParameters(rootNode* root,char* word,generalInfo* info){
	if(root == NULL){
		return;
	}
	
	if(root->start == NULL){
		return;
	}
	
	int frequencyWord = 0;
	trieNode* tempNode = root->start->firstNode;
	for(int i=0; i< strlen(word); i++){
		while(tempNode != NULL){
			if(tempNode->character == word[i]){
				if(i != strlen(word)-1){
					tempNode = tempNode->head->firstNode;
					break;
				}else{
					frequencyWord = searchPostList(tempNode->postList);
				}
			}else{
				tempNode = tempNode->nextNode;
			}
		}
		if(tempNode == NULL){
			return;
		}
	}
}


int searchPL(postingLists* list){
	while(list != NULL){
		list = list->next;
	}
	return 0;
}