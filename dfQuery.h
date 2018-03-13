#ifndef _DFQUERY_H_
#define _DFQUERY_H_

typedef struct stackNode{
	int alternatives;
	char character;
	int docFrequency;
	int lastChar;
}stackNode;

typedef struct stack{
	int size;
	int top;
	stackNode* elements;
}stack;

//df's functions
int retDocFrequency(rootNode* root,char* word);
void BFS(trieNode* node,stack* stackWord);

//stack's functions
void initializeStack(stack** stackWord,int size);
void destroyStack(stack** stackWord);
int stackIsEmpty(stack* stackWord);
int stackIsFull(stack* stackWord);
void doubleStack(stack* stackWord);
void stackPush(stack* stackWord,stackNode* node);
stackNode* stackPop(stack* stackWord);
void printStack(stack* stackWord);


#endif