#ifndef _INVERTEDINDEX_H_
#define _INVERTEDINDEX_H_

#include "index.h"


typedef struct trieN trieNode;
typedef struct levelQueue headQueue;

typedef struct postingListsNode{
	int id;
	int timesAppeared;
}postingListsNode;

typedef struct postingLists{
	postingListsNode* arrayPosting;
	int size;
}postingLists;

struct trieN{
	char character;
	trieNode *nextNode;
	headQueue *head;
	postingLists* postList;
}trieN;

struct levelQueue{
	trieNode* firstNode;
	int size;
}levelQueue;

typedef struct rootNode{
	headQueue* start;
}rootNode;


rootNode* createRoot();
headQueue* createHeadQueue();
void populateTrie(rootNode* root,mapIndex* index,int noElems);
void insertTrie(char* word,int id,rootNode* root);
void insertHeadQueue(rootNode* root,char c,int lastChar);
trieNode* createNode(char c,int lastChar);
postingLists* createPostList();
void doublePostList(postingLists* array);

#endif