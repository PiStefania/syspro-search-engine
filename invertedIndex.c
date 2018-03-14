#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "invertedIndex.h"

rootNode* createRoot(){
	rootNode* root = malloc(sizeof(rootNode));
	root->start = NULL;
	return root;
}

void populateTrie(rootNode* root,mapIndex* index,int noElems,generalInfo* info){
	char* tempWord = NULL;
	int counterWords = 0;
	for(int i=0;i<noElems;i++){
		int wordsSpecificDoc = 0;
		if(index[i].document == NULL)
			continue;
		
		tempWord = strtok(index[i].document," ");
		while(tempWord!=NULL){
			//insert to trie
			counterWords++;
			wordsSpecificDoc++;
			insertTrie(tempWord,i,root);
			tempWord = strtok(NULL," ");
		}
		index[i].words = wordsSpecificDoc;
	}
	info->totalWords = counterWords;
}

headQueue* createHeadQueue(){
	headQueue* head = malloc(sizeof(headQueue));
	head->firstNode = NULL;
	head->lastNode = NULL;
	head->size = 0;
}


trieNode* createNode(char c,int firstChar){
	trieNode* node = malloc(sizeof(trieNode));
	node->character = c;
	node->nextNode = NULL;
	node->head = NULL;
	node->postList = NULL;
	node->documentFrequency = 0;
	node->firstChar = firstChar;
	return node;
}

int insertPostList(postingLists** list,int id){
	if(*list == NULL){
		*list = malloc(sizeof(postingLists));
		(*list)->id = id;
		(*list)->timesAppeared = 1;
		(*list)->next = NULL;
		return 1;
	}else{
		postingLists* tempNode = *list;
		postingLists* lastNode = NULL;
		while(tempNode != NULL){
			lastNode = tempNode;
			if(tempNode->id == id){
				tempNode->timesAppeared++;
				return 0;
			}else{
				tempNode = tempNode->next;
			}
		}
		
		if(tempNode == NULL){
			lastNode->next = malloc(sizeof(postingLists));
			lastNode->next->id = id;
			lastNode->next->timesAppeared = 1;
			lastNode->next->next = NULL;
			return 1;
		}
	}
}


void insertTrie(char* word,int id,rootNode* root){
	if(root == NULL){
		root = createRoot();
	}
	
	if(root->start == NULL){
		root->start = createHeadQueue();
	}
	
	headQueue* head = root->start;
	for(int i=0; i<strlen(word); i++){
		char currentChar = word[i];
		int lastChar = 0;
		int firstChar = 0;
		if(i == strlen(word)-1)
			lastChar = 1;
		if(i==0){
			firstChar = 1;
		}
		head = insertCharacter(head,currentChar,id,lastChar,firstChar);
	}
}

headQueue* insertCharacter(headQueue* wordQueue,char c,int id,int lastChar,int firstChar){
	if(wordQueue == NULL){
		wordQueue = createHeadQueue();
		wordQueue->firstNode = createNode(c,firstChar);
		if(lastChar){
			int newNodeCreated = insertPostList(&wordQueue->firstNode->postList,id);
			if(newNodeCreated){
				wordQueue->firstNode->documentFrequency++;
			}
		}
		wordQueue->firstNode->head = createHeadQueue();
		wordQueue->lastNode = wordQueue->firstNode;
		wordQueue->size++;
		return wordQueue->firstNode->head;
	}
	
	trieNode* tempNode = wordQueue->firstNode;
	while(tempNode!=NULL){
		if(tempNode->character == c){
			if(lastChar){
				int newNodeCreated = insertPostList(&tempNode->postList,id);
				if(newNodeCreated){
					tempNode->documentFrequency++;
				}
			}
			return tempNode->head;
		}else{
			tempNode = tempNode->nextNode;
		}
	}

	if(wordQueue->firstNode == NULL){
		wordQueue->firstNode = createNode(c,firstChar);
		if(lastChar){
			int newNodeCreated = insertPostList(&wordQueue->firstNode->postList,id);
			if(newNodeCreated){
				wordQueue->firstNode->documentFrequency++;
			}
		}
		wordQueue->firstNode->head = createHeadQueue();
		wordQueue->lastNode = wordQueue->firstNode;
		wordQueue->size++;
		return wordQueue->firstNode->head;
	}else{
		wordQueue->lastNode->nextNode = createNode(c,firstChar);
		if(lastChar){
			int newNodeCreated = insertPostList(&wordQueue->lastNode->nextNode->postList,id);
			if(newNodeCreated){
				wordQueue->lastNode->nextNode->documentFrequency++;
			}
		}
		wordQueue->lastNode->nextNode->head = createHeadQueue();
		wordQueue->lastNode = wordQueue->lastNode->nextNode;
		wordQueue->size++;
		return wordQueue->lastNode->head;
	}
}

void destroyInvertedIndex(rootNode** root){
	destroyHeadQueues(&(*root)->start);
	free(*root);
	*root = NULL;
}

void destroyPostList(trieNode** node){
	postingLists* currentNode = (*node)->postList;
	postingLists* nextNode;
	while (currentNode != NULL){
		nextNode = currentNode->next;
		free(currentNode);
		currentNode = nextNode;
	}
	(*node)->postList = NULL;
}

void destroyHeadQueues(headQueue** head){
	headQueue* currentHead = *head;
	trieNode* currentNode = currentHead->firstNode;
	trieNode* next;
	while(currentNode != NULL){	
		destroyHeadQueues(&currentNode->head);
		//delete node
		next = currentNode->nextNode;
		destroyPostList(&currentNode);
		free(currentNode);
		currentNode = next;
		currentHead->size--;
	}
	free(currentHead);
	currentHead = NULL;

}
