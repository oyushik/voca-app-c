#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    // getch() is implemented in ui.c
    extern int getch(void);
#endif
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"

// Global flag to prevent infinite review loops
int reviewCompleted = 0;

// Start memory card game with specified mode (1=random, 2=alphabetical, 3=custom)
void startMemoryCardGame(LinkedList* head, const int mode)
{
    reviewCompleted = 0;

    if (head == NULL)
    {
        printf("\nNo more words to study.\n");
        return;
    }

    // Count total words
    int remaining = 0;
    LinkedList* current = head;
    while (current != NULL)
    {
        remaining++;
        current = current->pNext;
    }

    current = head;

    // Initialize review list for "Don't Know" words
    LinkedList* reviewListHead = NULL;
    LinkedList* reviewListTail = NULL;

    // Convert linked list to array for shuffling/sorting
    int count = remaining;
    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    int listSize = 0;

    while (current != NULL)
    {
        nodes[listSize++] = current;
        current = current->pNext;
    }

    // Apply ordering based on mode
    if (mode == 1)  // Random: shuffle using Fisher-Yates
    {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < count; i++)
        {
            int j = rand() % count;
            LinkedList* temp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = temp;
        }
    }
    else if (mode == 2)  // Alphabetical: sort
    {
        qsort(nodes, count, sizeof(LinkedList*), compareVoca);
    }
    // mode == 3: Custom order (no change needed)

    current = nodes[0];
    reviewListHead = memoryCardRecursion(mode, count, remaining, nodes, current, reviewListHead, reviewListTail);
    free(nodes);

    printf("\nYou have been checked all words.\n");

    // Prompt for review if there are "Don't Know" words
    if (reviewCompleted == 0)
    {
        checkIfReview(reviewListHead, mode);
    }
}

// Main game loop: iterate through words and collect "Don't Know" items
LinkedList* memoryCardRecursion(const int mode, const int count, int remaining,
    LinkedList** nodes, LinkedList* current, LinkedList* reviewListHead, LinkedList* reviewListTail)
{
    // Determine mode display text
    int i = 0;
    const char* modeText = 0;
    if (mode == 1)
    {
        modeText = "RANDOM";
    }
    else if (mode == 2)
    {
        modeText = "ALPHABET";
    }
    else
    {
        modeText = "CUSTOM";
    }

    while (i < count)
    {
        clearScreen();
        printf("---Memory Card game [%s]---\n", modeText);
        printf("Remaining: [ %d ]\n\n", remaining);

        printf("%s\n", nodes[i]->pVocaData->voca);
        printf("\n1. Know\n");
        printf("2. Don't Know\n\n");
        printf("Enter 1/2: ");

        const int choice = getValidInput();

        if (choice == 1)
        {
            printf("\nMeaning: %s\n", nodes[i]->pVocaData->mean);
        }
        else if (choice == 2)
        {
            printf("\nMeaning: %s\n", nodes[i]->pVocaData->mean);

            // Add to review list for later practice
            LinkedList* newNode = createNode(nodes[i]->pVocaData->voca, nodes[i]->pVocaData->mean);
            if (reviewListHead == NULL)
            {
                reviewListHead = reviewListTail = newNode;
            }
            else
            {
                reviewListTail->pNext = newNode;
                newNode->pPrev = reviewListTail;
                reviewListTail = newNode;
            }
        }
        else
        {
            printf("Invalid input. Please enter a valid number.\n");
            getch();
            continue;
        }
        remaining--;

        printf("\nEnter any key to next!");
        getch();
        i++;
    }

    return reviewListHead;
}

const int countReviewList(LinkedList* reviewListHead)
{
    int count = 0;
    while (reviewListHead != NULL)
    {
        count++;
        reviewListHead = reviewListHead->pNext;
    }
    return count;
}

// Prompt user to review "Don't Know" words (recursive spaced repetition)
void checkIfReview(LinkedList* reviewListHead, const int mode)
{
    if (reviewListHead != NULL)
    {
        const int cntDontKnow = countReviewList(reviewListHead);

        while (1)
        {
            clearScreen();
            printf("[ %d ] words you select 'Don't Know'.\n\n", cntDontKnow);
            printf("Do you want to review 'Don't Know' words?\n\n");
            printf("YES:\tEnter '1'\n");
            printf("NO:\tEnter '2'\n\n");
            printf("Enter 1/2: ");

            const int reviewChoice = getValidInput();

            if (reviewChoice == 1)
            {
                // Recursively review "Don't Know" words
                startMemoryCardGame(reviewListHead, mode);
                break;
            }
            else if (reviewChoice == 2)
            {
                printf("\nReview Over!");
                reviewCompleted = 1;
                getch();
                break;
            }
            else
            {
                printf("Invalid input. Press any key to try again...\n");
                getch();
                continue;
            }
        }
    }
    else
    {
        printf("\nNo words to review.\n");
        reviewCompleted = 1;
        getch();
    }
}
