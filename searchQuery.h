#ifndef _SEARCHQUERY_H_
#define _SEARCHQUERY_H_

#include "invertedIndex.h"

typedef struct scoreNode{
	int id;
	char* words;
	int score;
}scoreNode;

void getScoreParameters(rootNode* root,char* word,generalInfo* info);
int searchPL(postingLists* list);

#endif