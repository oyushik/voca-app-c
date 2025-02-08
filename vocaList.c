#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"


// Function to create a new node
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

    // Copy values to voca and mean
    strncpy(newNode->pVocaData->voca, voca, LEN);
    strncpy(newNode->pVocaData->mean, mean, LEN);

    newNode->pPrev = NULL;
    newNode->pNext = NULL;

    return newNode;
}

// Function to create a LinkedList from a file
LinkedList* createLinkedListFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("ERROR: Failed to open the file\n");
        return NULL;
    }

    LinkedList* head = NULL;  // Pointer to the start of the list
    LinkedList* tail = NULL;  // Pointer to the end of the list

    char voca[LEN];
    char mean[LEN];

    while (fscanf(file, "%s %[^\n]", voca, mean) != EOF) // Read voca and mean from file
    {
        LinkedList* newNode = createNode(voca, mean);  // Create a new node

        if (newNode == NULL)
        {
            fclose(file);
            return NULL;
        }

        // If it's the first node
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        // If it's not the first node
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

// Function to print the contents of the list (entire voca and mean)
void printLinkedList(LinkedList* head, const int option)
{
    LinkedList* current = head;
    while (current != NULL)
    {
        if (option == 1)  // Print entire voca and mean
        {
            printf("%s : %s\n", current->pVocaData->voca, current->pVocaData->mean);
        }
        else if (option == 2)  // Print only voca
        {
            printf("%s\n", current->pVocaData->voca);
        }
        else if (option == 3)  // Print only mean
        {
            printf("%s\n", current->pVocaData->mean);
        }
        current = current->pNext;
    }
}

// Function to shuffle and print the list
void printShuffledLinkedList(LinkedList* head, const int option)
{
    // Count the number of nodes
    int count = 0;
    LinkedList* current = head;
    while (current != NULL)
    {
        count++;
        current = current->pNext;
    }

    // If there's only one node, no need to shuffle
    if (count < 2) return;

    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    current = head;
    for (int i = 0; i < count; i++)
    {
        nodes[i] = current;
        current = current->pNext;
    }

    // Shuffle the nodes
    srand((unsigned int)time(NULL));  // Set random seed
    for (int i = 0; i < count; i++)
    {
        int j = rand() % count;
        LinkedList* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    // Print the shuffled nodes
    for (int i = 0; i < count; i++)
    {

        if (option == 1)  // Print entire voca and mean
        {
            printf("%s : %s\n", nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
        }
        else if (option == 2)  // Print only voca
        {
            printf("%s\n", nodes[i]->pVocaData->voca);
        }
        else if (option == 3)  // Print only mean
        {
            printf("%s\n", nodes[i]->pVocaData->mean);
        }
    }

    // Free memory
    free(nodes);
}

// Function to free the memory of the LinkedList
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

// Comparison function for qsort
int compareVoca(const void* a, const void* b)
{
    LinkedList* nodeA = *((LinkedList**)a);
    LinkedList* nodeB = *((LinkedList**)b);
    return strcmpi(nodeA->pVocaData->voca, nodeB->pVocaData->voca);
}

// Function to initialize the list at the start of the program
void initList()
{
    // Create the original LinkedList from file
    head = createLinkedListFromFile(filename);
    if (head == NULL)
    {
        puts("ERROR: Head is NULL");
        return;
    }

    // Create a sorted LinkedList (using qsort)
    sortedHead = createLinkedListFromFile(filename);
    LinkedList* current = sortedHead;
    int nodeCount = 0;

    // Store the nodes of the list in an array
    LinkedList* nodes[100]; // Store up to 100 nodes (adjust as needed)
    while (current != NULL)
    {
        nodes[nodeCount++] = current;
        current = current->pNext;
    }

    // Sort the array using qsort
    qsort(nodes, nodeCount, sizeof(LinkedList*), compareVoca);

    // Recreate the linked list with sorted nodes
    for (int i = 0; i < nodeCount - 1; i++)
    {
        nodes[i]->pNext = nodes[i + 1];
        nodes[i + 1]->pPrev = nodes[i];
    }
    nodes[nodeCount - 1]->pNext = NULL;
    nodes[0]->pPrev = NULL;

    sortedHead = nodes[0];  // Head of the sorted list
}
