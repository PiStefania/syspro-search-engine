#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "variousMethods.h"
#include "tfQuery.h"
#include "dfQuery.h"
#include "searchQuery.h"

#define MAX_WORDS 10
#define STACK_SIZE 10

void pickArgumentsMain(int argc,char* argv[],char** docfile,int* K){
	
	char* noOfK = NULL;
	
	if(argc == 5){
		for(int i=0; i<argc; i++){
			if(strcmp(argv[i],"-i")==0)
				*docfile=argv[i+1];			
			if(strcmp(argv[i],"-k")==0)
				noOfK=argv[i+1];
		}
	}
	else if(argc == 3){
		for(int i=0; i<argc; i++){
			if(strcmp(argv[i],"-i")==0)
				*docfile=argv[i+1];			
		}
	}
	else{
		printf("Wrong number of arguments. Terminate process.\n");
		exit(1);
	}
	
	if(*docfile == NULL){
		printf("Error! Wrong Arguments!\n");
		exit(1);
	}
	
	if(noOfK == NULL && argc == 3){
		*K = 10;
	}else if(noOfK == NULL && argc == 5){
		printf("Error getting value of K. Terminate process.\n");
		exit(1);
	}else{
		*K = atoi(noOfK);
	}
	
	if(*K == 0){
		printf("Error K = 0. Terminate process.\n");
		exit(1);
	}
}

int checkFileGetLines(FILE *fp){
	int read;
	size_t len = 0;
	int lines = 0;
	
	//change after
	int counterIds = 0;
	int id;
	char* line = NULL;
	while((read = getline(&line, &len, fp)) != -1){
		//check line whitespace
		char* temp = strtok(line,"\n");
		if(temp == NULL){
			continue;
		}
		temp = strtok(temp," \t");
		if(temp == NULL){
			continue;
		}
		
		//check ids
		id = atoi(temp);
		if(id == counterIds){
			lines++;
			counterIds++;
		}else{
			free(temp);
			temp = NULL;
			return -1;
		}
		
		
	}
	if(line){
		free(line);
		line = NULL;
	}
	
	return lines;
}

void optionsUserInput(int K,rootNode* root,generalInfo* info,mapIndex* index){
	int read;
	size_t len = 0;
	char* line = NULL;
	char* token = NULL;
	printf("Input desirable query: \n");
	while(1){
		printf("Reminder ('/search %d words', '/df', '/df word', '/tf id word', '/exit').\n",K);
		if((read = getline(&line, &len, stdin)) != -1){
			line = strtok(line,"\n");
			if(line == NULL){
				continue;
			}
			token = strtok(line," ");
			if(strcmp(line,"/exit")==0 || strcmp(line,"\\exit")==0){
				printf("Exiting process.\n");
				break;
			}else if(strcmp(token,"\\search")==0 || strcmp(token,"/search")==0){
				token = strtok(NULL," ");
				if(token == NULL){
					printf("Search query with no search words.Terminating process.\n");
					break;
				}
				int words = 1;
				
				scores* scoresArray = createScoresArray(); 
				while(token!=NULL){
					//search		
					calculateScoresWord(root,token,info,scoresArray,index);
					//last word
					if(words == MAX_WORDS){
						break;
					}
					token = strtok(NULL," ");
					words++;
				}
				
				//print k scores
				heapSort(scoresArray);
				printMaxKScores(scoresArray,index,K);
				destroyScoresArray(&scoresArray);
			}else if(strcmp(token,"/df")==0 || strcmp(token,"\\df")==0){
				token = strtok(NULL," ");
				if(token == NULL){
					//return all
					stack* stackWord = malloc(sizeof(stack));
					initializeStack(&stackWord,STACK_SIZE);					
					DFS(root->start->firstNode,stackWord);
					destroyStack(&stackWord);
				}else{
					//return df of specific word
					int specificDocumentFrequency = retDocFrequency(root,token);
					if(specificDocumentFrequency == -1){
						printf("An error occured.Terminating process.\n");
						break;
					}else if(specificDocumentFrequency == -2 || specificDocumentFrequency == 0){
						printf("Not found.\n");
					}else{
						printf("%s %d\n",token,specificDocumentFrequency);
					}
				}
			}else if(strcmp(token,"/tf")==0 || strcmp(token,"\\tf")==0){
				token = strtok(NULL," ");
				if(token == NULL){
					printf("Tf query with no document id.Terminating process.\n");
					break;
				}
				int id = atoi(token);
				if(id == 0 && token[0]!='0'){
					printf("Tf query with false document id.Terminating process.\n");
					break;
				}
				char* word = strtok(NULL," ");
				if(word == NULL){
					printf("Tf query with no search word.Terminating process.\n");
					break;
				}
				
				int timesAppeared = returnTimesAppeared(root,id,word);
				if(timesAppeared == -1){
					printf("An error occured.Terminating process.\n");
					break;
				}else if(timesAppeared == -2 || timesAppeared == 0){
					printf("Not found.\n");
				}else{
					printf("%d %s %d\n",id,word,timesAppeared);
				}
				
			}else{
				printf("Your input is not a query.Terminating process.\n");				
				break;
			}
		}
		if(read == -1)
			break;
	}
	
	free(line);
	line = NULL;
}
