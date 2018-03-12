#ifndef _INVERTEDINDEX_H_
#define _INVERTEDINDEX_H_

#include "index.h"


typedef struct trieN trieNode;
typedef struct levelQueue headQueue;
typedef struct postingListsNode postingLists;

struct postingListsNode{
	int id;
	int timesAppeared;
	postingLists* next;
}postingListsNode;

struct trieN{
	char character;
	trieNode *nextNode;
	headQueue *head;
	postingLists* postList;
	int documentFrequency;
}trieN;

struct levelQueue{
	trieNode* firstNode;
	trieNode* lastNode;
	int size;
}levelQueue;

typedef struct rootNode{
	headQueue* start;
}rootNode;


rootNode* createRoot();
headQueue* createHeadQueue();
void populateTrie(rootNode* root,mapIndex* index,int noElems);
void insertTrie(char* word,int id,rootNode* root);
headQueue* insertCharacter(headQueue* wordQueue,char c,int id,int lastChar);
trieNode* createNode(char c);
int insertPostList(postingLists** list,int id);
void destroyInvertedIndex(rootNode** root);
void destroyPostList(trieNode** node);
void destroyHeadQueues(headQueue** head);

#endif