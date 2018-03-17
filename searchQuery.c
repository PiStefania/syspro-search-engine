#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "searchQuery.h"
#include "generalInfo.h"
#define INIT_SIZE 10


void printMaxKScores(){

}

void heapify(scores* scoresArray, int n, int i){
	int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    if (l < n && scoresArray->scoreArray[l].score < scoresArray->scoreArray[largest].score)
        largest = l;

    if (r < n && scoresArray->scoreArray[r].score < scoresArray->scoreArray[largest].score)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        scoreNode temp = scoresArray->scoreArray[i];
		scoresArray->scoreArray[i] = scoresArray->scoreArray[largest];
		scoresArray->scoreArray[largest] = temp;
		heapify(scoresArray, n, largest);
    }
}

void buildHeap(scores* scoresArray){
	for(int i = (scoresArray->actualSize) / 2; i >= 0; i--){
		heapify(scoresArray,scoresArray->actualSize,i);
	}
}

void heapSort(scores* scoresArray){
    buildHeap(scoresArray);
    for (int i=scoresArray->actualSize-1; i>=0; i--)
    {
        scoreNode temp = scoresArray->scoreArray[0];
		scoresArray->scoreArray[0] = scoresArray->scoreArray[i];
		scoresArray->scoreArray[i] = temp;
        heapify(scoresArray, i, 0);
    }
}

void calculateScoresWord(rootNode* root,char* word,generalInfo* info,scores* scoresArray,mapIndex* index){
	if(root == NULL){
		return;
	}
	
	if(root->start == NULL){
		return;
	}
	
	trieNode* tempNode = root->start->firstNode;
	for(int i=0; i < strlen(word); i++){
		while(tempNode != NULL){
			if(tempNode->character == word[i]){
				if(i != strlen(word)-1){
					tempNode = tempNode->head->firstNode;
					break;
				}else{
					//last char
					if(tempNode->postList != NULL){
						insertEachPostNode(scoresArray,tempNode,info,index,word);
					}
					return;
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

void insertEachPostNode(scores* scoresArray,trieNode* node,generalInfo* info,mapIndex* index,char* word){
	postingLists* tempNode = node->postList;
	while(tempNode != NULL){
		scoreNode* insertNode = malloc(sizeof(scoreNode));
		insertNode->id = tempNode->id;
		insertNode->score = calculateScore(info,node->documentFrequency,tempNode,index);
		insertNode->words = malloc((strlen(word)+1)*sizeof(char));
		strcpy(insertNode->words,word);
		insertionSortScores(scoresArray,insertNode);
		tempNode = tempNode->next;
	}
}

void insertionSortScores(scores* scoresArray, scoreNode* insertNode){
	int getPosition = binarySearchScores(scoresArray,insertNode->id);
	
	if(scoresArray->actualSize == scoresArray->size-1){
		doubleScoresArray(scoresArray);
	}
	
	if(scoresArray->actualSize == 0){
		//empty
		copyDataScore(insertNode,&scoresArray->scoreArray[0]);
		scoresArray->actualSize++;
	}else{
		//same id
		if(insertNode->id == scoresArray->scoreArray[getPosition].id){
			scoresArray->scoreArray[getPosition].score += insertNode->score;
			scoresArray->scoreArray[getPosition].words = realloc(scoresArray->scoreArray[getPosition].words,(strlen(scoresArray->scoreArray[getPosition].words) + 2 + strlen(insertNode->words))*sizeof(char));
			strcat(scoresArray->scoreArray[getPosition].words," ");
			strcat(scoresArray->scoreArray[getPosition].words,insertNode->words);
		}else{
			int fullMoveSize = (scoresArray->actualSize - getPosition)*sizeof(scoresArray->scoreArray[scoresArray->actualSize]);
			memmove(&(scoresArray->scoreArray[getPosition+1]), &(scoresArray->scoreArray[getPosition]), fullMoveSize);
			copyDataScore(insertNode,&scoresArray->scoreArray[getPosition]);
			scoresArray->actualSize++;
		}
	}
	
	free(insertNode->words);
	insertNode->words = NULL;
	free(insertNode);
	insertNode = NULL;
}

void copyDataScore(scoreNode* oldNode,scoreNode* newNode){
	newNode->id = oldNode->id;
	newNode->words = malloc((strlen(oldNode->words)+1)*sizeof(char));
	strcpy(newNode->words, oldNode->words);
	newNode->score = oldNode->score;
}

int binarySearchScores(scores* scoresArray, int id){
	int first = 0;
	int last = scoresArray->actualSize;
	int mid = 0;
	scoreNode* array = scoresArray->scoreArray;
	while (first < last){
        int mid = first + (last-first)/2;
        if(array[mid].id == id)
            return mid;
        if (array[mid].id < id)
            first = mid + 1;
		else
            last = mid - 1;
    }
	if(last<=first){
		if(id > scoresArray->scoreArray[first].id && scoresArray->scoreArray[first].id!=-1)
			return first+1;
		else
			return first;
	}
    return mid;
}

void printScoresArray(scores* scoresArray){
	for(int i=0;i<scoresArray->actualSize;i++){
		printf("%dth elem with id: %d and score: %lf and words: '%s'\n",i,scoresArray->scoreArray[i].id,scoresArray->scoreArray[i].score,scoresArray->scoreArray[i].words);
	}
}


double calculateScore(generalInfo* info,int docFrequency,postingLists* node,mapIndex* index){
	double idfDivision = (double) (info->totalDocuments - docFrequency + 0.5) / (docFrequency + 0.5);
	double IDF = log10(idfDivision);
	double fQi = (double) node->timesAppeared;
	double D = (double) index[node->id].words;
	double N = (double) info->totalDocuments;
	double avgdl = (double) info->totalWords / N;
	double k1 = (double) info->k1;
	double b = (double) info->b;
	double score = IDF * ((fQi*(k1+1))/(fQi + k1*(1-b + (b*(D/avgdl)))));
	return score;
}


//funcs for scores node
scores* createScoresArray(){
	scores* scoresArray = malloc(sizeof(scores));
	scoresArray->size = INIT_SIZE;
	scoresArray->actualSize = 0;
	scoresArray->scoreArray = malloc(INIT_SIZE*sizeof(scoreNode));
	for(int i=0;i<scoresArray->size;i++){
		scoresArray->scoreArray[i].id = -1;
		scoresArray->scoreArray[i].words = NULL;
		scoresArray->scoreArray[i].score = 0;
	}
	return scoresArray;
}

void doubleScoresArray(scores* scoresArray){
	int oldSize = scoresArray->size;
	scoresArray->scoreArray = realloc(scoresArray->scoreArray,2*oldSize*sizeof(scoreNode));
	scoresArray->size = 2*oldSize;
	for(int i=oldSize; i<scoresArray->size;i++){
		scoresArray->scoreArray[i].id = -1;
		scoresArray->scoreArray[i].words = NULL;
		scoresArray->scoreArray[i].score = 0;
	}
}

void destroyScoresArray(scores** scoresArray){
	for(int i=0; i < (*scoresArray)->actualSize;i++){
		free((*scoresArray)->scoreArray[i].words);
		(*scoresArray)->scoreArray[i].words = NULL;
	}
	free((*scoresArray)->scoreArray);
	(*scoresArray)->scoreArray = NULL;
	free((*scoresArray));
	(*scoresArray) = NULL;
}
