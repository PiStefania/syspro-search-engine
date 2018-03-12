#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invertedIndex.h"
#include "tfQuery.h"

int returnTimesAppeared(rootNode* root,int id,char* word){
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
					return searchPostList(tempNode->postList,id);
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

int searchPostList(postingLists* list,int id){
	while(list != NULL){
		if(list->id == id){
			return list->timesAppeared;
		}else{
			list = list->next;
		}
	}
	return 0;
}




