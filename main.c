#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include "variousMethods.h"

int main (int argc,char* argv[]){
	
	int K=0;
	char* docfile = NULL;
	pickArgumentsMain(argc,argv,&docfile,&K);
	
	FILE *inFile;
	inFile = fopen(docfile,"r");
	mapIndex* index = NULL;
	int lines = 0;
	if(inFile!=NULL)
	{
		lines = checkFileGetLines(inFile);
		if(lines == -1){
			printf("IDs set is incorrect.Terminate process.\n");
			fclose(inFile);
			exit(1);
		}else{
			rewind(inFile);
			index = populateIndex(lines,inFile);
		}
		fclose (inFile);
	}
	
	printMapIndex(index,lines);
	destroyMapIndex(index,lines);
	
	return 0;
}