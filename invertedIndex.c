#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invertedIndex.h"
#define INIT_POSTING 5

rootNode* createRoot(){
	rootNode* root = malloc(sizeof(rootNode));
	root->start = NULL;
	return root;
}

void populateTrie(rootNode* root,mapIndex* index,int noElems){
	char* tempWord = NULL;
	for(int i=0;i<noElems;i++){
		if(index[i].document == NULL)
			continue;
		
		tempWord = strtok(index[i].document," ");
		while(tempWord!=NULL){
			//insert to trie
			tempWord = strtok(NULL," ");
		}
	}
}

headQueue* createHeadQueue(){
	headQueue* head = malloc(sizeof(headQueue));
	head->firstNode = NULL;
	head->size = 0;
}

void insertHeadQueue(rootNode* root,char c,int lastChar){
	headQueue* head = root->start;
	trieNode* tempNode = head->firstNode;
	while(tempNode!=NULL){
		if(tempNode->character == c){
			break;
		}
		else{
			tempNode = tempNode->nextNode;
		}
	}

	//not found -> create one
	if(tempNode == NULL){
		
	}else{						//found go to next headQueue and repeat
	
	}
}


trieNode* createNode(char c,int lastChar){
	trieNode* node = malloc(sizeof(trieNode));
	node->character = c;
	node->nextNode = NULL;
	node->head = NULL;
	
	//last char
	if(lastChar){
		node->postList = createPostList();	
	}
}

postingLists* createPostList(){
	postingLists* array = malloc(sizeof(postingLists));
	array->arrayPosting = malloc(INIT_POSTING*sizeof(postingListsNode));
	array->size = INIT_POSTING;
}

void doublePostList(postingLists* array){
	int prevSize = array->size;
	array->arrayPosting = realloc(array->arrayPosting,(prevSize*2)*sizeof(postingListsNode));
	array->size = prevSize*2;
}


void insertTrie(char* word,int id,rootNode* root){
	if(root == NULL)
		root = createRoot();
	
	if(root->start == NULL)
		root->start = createHeadQueue();
	
	for(int i=0; i<strlen(word); i++){
		char currentChar = word[i];
		int lastChar = 0;
		if(i == strlen(word)-1)
			lastChar = 1;
		
		insertHeadQueue(root,currentChar,lastChar);
	}

}