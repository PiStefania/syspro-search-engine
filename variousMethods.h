#ifndef _VARIOUSMETHODS_H_
#define _VARIOUSMETHODS_H_

#include "invertedIndex.h"


void pickArgumentsMain(int argc,char* argv[],char** docfile,int* K);
int checkFileGetLines(FILE *fp);
void optionsUserInput(int K,rootNode* root);

#endif