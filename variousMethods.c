#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "variousMethods.h"

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
