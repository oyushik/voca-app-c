#pragma once

#define LEN 64

typedef struct VocaStruct
{
    char voca[LEN];
    char mean[LEN];
} VocaStruct;

typedef struct LinkedList
{
    VocaStruct* pVocaData;
    struct LinkedList* pPrev;
    struct LinkedList* pNext;
} LinkedList;

extern LinkedList* head;
extern LinkedList* sortedHead;

extern const char* filename;

LinkedList* createNode(const char* voca, const char* mean);

LinkedList* createLinkedListFromFile(const char* filename);

void printLinkedList(LinkedList* head, const int option);

void printShuffledLinkedList(LinkedList* head, const int option);

void freeLinkedList(LinkedList* head);

int compareVoca(const void* a, const void* b);

void initList();
