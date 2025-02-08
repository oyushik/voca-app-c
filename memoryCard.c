#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"


void startMemoryCardGame(LinkedList* head, const int mode)
{
    reviewCompleted = 0;

    if (head == NULL)
    {
        printf("\nNo more words to study.\n");
        return;
    }

    int remaining = 0;
    LinkedList* current = head;

    // Count the number of words
    while (current != NULL)
    {
        remaining++;
        current = current->pNext;
    }

    current = head;

    // List to store words selected as 'Don't Know'
    LinkedList* reviewListHead = NULL;
    LinkedList* reviewListTail = NULL;

    int count = remaining;
    LinkedList** nodes = (LinkedList**)malloc(count * sizeof(LinkedList*));
    int listSize = 0;

    while (current != NULL)
    {
        nodes[listSize++] = current;
        current = current->pNext;
    }

    if (mode == 1)
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
    else if (mode == 2)
    {
        qsort(nodes, count, sizeof(LinkedList*), compareVoca);
    }

    current = nodes[0];
    reviewListHead = memoryCardRecursion(mode, count, remaining, nodes, current, reviewListHead, reviewListTail);
    free(nodes);

    // Print message when the game is over
    printf("\nYou have been checked all words.\n");

    // Check if there are words selected as 'Don't Know' for review
    if (reviewCompleted == 0)  // Only show if review is not completed
    {
        checkIfReview(reviewListHead, mode);
    }
}

LinkedList* memoryCardRecursion(const int mode, const int count, int remaining,
    LinkedList** nodes, LinkedList* current, LinkedList* reviewListHead, LinkedList* reviewListTail)
{
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

            // Add words selected as 'Don't Know' to the review list
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
        remaining--;  // Decrease the number of remaining words

        // Wait for user input and move to the next card
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

void checkIfReview(LinkedList* reviewListHead, const int mode)
{
    if (reviewListHead != NULL)  // Check if there are words in the 'Don't Know' list
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
                // Start review game
                startMemoryCardGame(reviewListHead, mode);  // Recursively start review
                break;
            }
            else if (reviewChoice == 2)
            {
                printf("\nReview Over!");
                reviewCompleted = 1;  // Set flag as review not done
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
        reviewCompleted = 1;  // Set flag as no words to review
        getch();
    }
}
