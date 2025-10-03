#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#endif
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"


// Create a new doubly-linked list node with vocabulary data
LinkedList* createNode(const char* voca, const char* mean)
{
    LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));

    if (!newNode)
    {
        printf("ERROR: Failed to allocate the memory\n");
        return NULL;
    }

    newNode->pVocaData = (VocaStruct*)malloc(sizeof(VocaStruct));
    if (!(newNode->pVocaData))
    {
        printf("ERROR: Failed to allocate the memory\n");
        free(newNode);
        return NULL;
    }

    strncpy(newNode->pVocaData->voca, voca, LEN);
    strncpy(newNode->pVocaData->mean, mean, LEN);

    newNode->pPrev = NULL;
    newNode->pNext = NULL;

    return newNode;
}

// Parse file and create linked list (format: "word meaning\n")
LinkedList* createLinkedListFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("ERROR: Failed to open the file\n");
        return NULL;
    }

    LinkedList* head = NULL;
    LinkedList* tail = NULL;

    char voca[LEN];
    char mean[LEN];

    // Read each line: first token is word, rest is meaning
    while (fscanf(file, "%s %[^\n]", voca, mean) != EOF)
    {
        LinkedList* newNode = createNode(voca, mean);

        if (newNode == NULL)
        {
            fclose(file);
            return NULL;
        }

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->pNext = newNode;
            newNode->pPrev = tail;
            tail = newNode;
        }
    }

    fclose(file);
    return head;
}

// Print list in order (option: 1=both, 2=word only, 3=meaning only)
void printLinkedList(LinkedList* head, const int option)
{
    LinkedList* current = head;
    while (current != NULL)
    {
        if (option == 1)
        {
            printf("%s : %s\n", current->pVocaData->voca, current->pVocaData->mean);
        }
        else if (option == 2)
        {
            printf("%s\n", current->pVocaData->voca);
        }
        else if (option == 3)
        {
            printf("%s\n", current->pVocaData->mean);
        }
        current = current->pNext;
    }
}

// Shuffle list using Fisher-Yates algorithm and print
void printShuffledLinkedList(LinkedList* head, const int option)
{
    // Count nodes
    int count = 0;
    LinkedList* current = head;
    while (current != NULL)
    {
        count++;
        current = current->pNext;
    }

    if (count < 2) return;

    // Convert to array for shuffling
    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    current = head;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->pNext;
    }

    // Fisher-Yates shuffle
    srand((unsigned int)time(NULL));
    for (int i = 0; i < count; i++)
    {
        int j = rand() % count;
        LinkedList* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    // Print shuffled order
    for (int i = 0; i < count; i++)
    {

        if (option == 1)
        {
            printf("%s : %s\n", nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
        }
        else if (option == 2)
        {
            printf("%s\n", nodes[i]->pVocaData->voca);
        }
        else if (option == 3)
        {
            printf("%s\n", nodes[i]->pVocaData->mean);
        }
    }

    free(nodes);
}

// Free all nodes in the linked list
void freeLinkedList(LinkedList* head)
{
    LinkedList* current = head;
    LinkedList* temp;

    while (current != NULL)
    {
        temp = current;
        current = current->pNext;
        free(temp->pVocaData);
        free(temp);
    }
}

// Case-insensitive comparison for qsort
int compareVoca(const void* a, const void* b)
{
    LinkedList* nodeA = *((LinkedList**)a);
    LinkedList* nodeB = *((LinkedList**)b);
#ifdef _WIN32
    return strcmpi(nodeA->pVocaData->voca, nodeB->pVocaData->voca);
#else
    return strcasecmp(nodeA->pVocaData->voca, nodeB->pVocaData->voca);
#endif
}

// Initialize global lists: original order and alphabetically sorted
void initList()
{
    // Create original list from file
    head = createLinkedListFromFile(filename);
    if (head == NULL)
    {
        puts("ERROR: Head is NULL");
        return;
    }

    // Create sorted list
    sortedHead = createLinkedListFromFile(filename);
    LinkedList* current = sortedHead;
    int nodeCount = 0;

    // Convert to array for sorting (max 100 words)
    LinkedList* nodes[100];
    while (current != NULL)
    {
        nodes[nodeCount++] = current;
        current = current->pNext;
    }

    // Sort alphabetically
    qsort(nodes, nodeCount, sizeof(LinkedList*), compareVoca);

    // Reconnect links in sorted order
    for (int i = 0; i < nodeCount - 1; i++)
    {
        nodes[i]->pNext = nodes[i + 1];
        nodes[i + 1]->pPrev = nodes[i];
    }
    nodes[nodeCount - 1]->pNext = NULL;
    nodes[0]->pPrev = NULL;

    sortedHead = nodes[0];
}
