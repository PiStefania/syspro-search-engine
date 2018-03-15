#ifndef _GENERALINFO_H_
#define _GENERALINFO_H_

typedef struct generalInfo{
	int totalWords;
	int totalDocuments;
	int k1;
	int b;
}generalInfo;


void initializeGeneralInfo(generalInfo** info);
void destroyGeneralInfo(generalInfo** info);

#endif