#ifndef _INVERTEDINDEX_H_
#define _INVERTEDINDEX_H_

typedef struct trieN trieNode;
typedef struct levelQueue headQueue;

struct trieN{
	char character;
	trieNode *nextNode;
	headQueue *head;
}trieN;

struct levelQueue{
	trieNode* firstNode;
	int size;
}levelQueue;

typedef struct postingListsNode{
	int id;
	int timesAppeared;
}postingListsNode;

typedef struct postingLists{
	postingListsNode* arrayPosting;
	int size;
}postingLists;


#endif