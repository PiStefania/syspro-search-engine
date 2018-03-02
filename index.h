#ifndef _INDEX_H_
#define _INDEX_H_

typedef struct mapIndex{
	int id;
	char* document;
}mapIndex;


mapIndex* populateIndex(int lines,FILE *fp);
void printMapIndex(mapIndex* index,int noElems);
void destroyMapIndex(mapIndex* index,int noElems);

#endif
