#ifndef _GENERALINFO_H_
#define _GENERALINFO_H_

typedef struct generalInfo{
	int totalWords;
	int totalDocuments;
	double k1;
	double b;
}generalInfo;


void initializeGeneralInfo(generalInfo** info);
void destroyGeneralInfo(generalInfo** info);

#endif