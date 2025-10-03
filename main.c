#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"

// Global vocabulary lists
LinkedList* head = NULL;         // Original order from file
LinkedList* sortedHead = NULL;   // Alphabetically sorted

// Vocabulary file format: "word meaning\n"
const char* filename = "vocabulary.txt";

int main(void)
{
    // Set UTF-8 encoding for multilingual support
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#else
    setlocale(LC_ALL, "");
#endif

    // Load vocabulary and start main menu
    initList();
    selectMenu();

    // Cleanup
    freeLinkedList(head);
    freeLinkedList(sortedHead);

    return 0;
}
