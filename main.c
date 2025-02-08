#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"

LinkedList* head = NULL;         // Original List
LinkedList* sortedHead = NULL;   // Sorted List

// .txt file with "word meaning\n"
const char* filename = "vocabulary.txt";

int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    initList();
    selectMenu();

    freeLinkedList(head);
    freeLinkedList(sortedHead);

    return 0;
}
