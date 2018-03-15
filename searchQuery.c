#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searchQuery.h"

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
					frequencyWord = searchPL(tempNode->postList);
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