#ifndef _SEARCHQUERY_H_
#define _SEARCHQUERY_H_

#include "invertedIndex.h"

typedef struct generalInfo{
	int totalWords;
	int totalDocuments;
	int k1;
	int b;
}generalInfo;

typedef struct scoreNode{
	int id;
	char* words;
	int score;
}scoreNode;


//functions for generalInfo
void initializeGeneralInfo(generalInfo** info);
void destroyGeneralInfo(generalInfo** info);

//functions for scoreNode
void getScoreParameters(rootNode* root,char* word,generalInfo* info);
int searchPL(postingLists* list);

#endif