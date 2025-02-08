#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "vocaList.h"
#include "memoryCard.h"
#include "ui.h"


void clearScreen()
{
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/macOS
#endif
}


int getValidInput()
{
    int choice;
    char buffer[100];

    while (1)
    {

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';

            if (buffer[0] == '\0')
            {
                putchar('\n');
                break;
            }

            if (sscanf(buffer, "%d", &choice) == 1)
            {
                putchar('\n');
                return choice;
            }
            else
            {
                putchar('\n');
                break;
            }
        }
        else
        {
            printf("Error reading input. Please try again.\n");
            break;
        }
    }
}

void printMenu()
{
    clearScreen();

    const char* menu[] =
    {
        "Welcome to Voca!",
        "",
        "---[RANDOM]---",
        "1. Whole",
        "2. Voca Only",
        "3. Meaning Only",
        "",
        "---[ALPHABET]---",
        "4. Whole",
        "5. Voca Only",
        "6. Meaning Only",
        "",
        "---[CUSTOM]---",
        "7. Whole",
        "8. Voca Only",
        "9. Meaning Only",
        "",
        "100. Memory Card game [RANDOM]",
        "101. Memory Card game [ALPHABET]",
        "102. Memory Card game [CUSTOM]",
        "",
        "0. EXIT",
    };

    int menuHeight = sizeof(menu) / sizeof(menu[0]);
    int menuWidth = 0;

    for (int i = 0; i < menuHeight; i++)
    {
        int len = strlen(menu[i]);

        if (len > menuWidth)
        {
            menuWidth = len;
        }
    }

    int screenWidth = 80;
    int screenHeight = 25;

    int startX = (screenWidth - menuWidth) / 2;
    int startY = (screenHeight - menuHeight) / 2;

    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    for (int i = 0; i < menuHeight; i++)
    {
        int leftPadding = (screenWidth - menuWidth) / 2;

        for (int j = 0; j < leftPadding; j++)
        {
            printf(" ");
        }

        printf("| %s", menu[i]);

        int rightPadding = screenWidth - leftPadding - strlen(menu[i]) - 2; // ¾ç ¿· '|' Á¦¿Ü
        for (int j = 0; j < rightPadding; j++)
        {
            printf(" ");
        }

        printf("|\n");
    }

    for (int i = 0; i < screenWidth; i++)
    {
        printf("-");
    }

    printf("\n");

    printf("\nEnter the number (1~9, 100~102, or 0 to Exit): ");
}

void selectMenu()
{
    int choice;
    do
    {
        printMenu();

        choice = getValidInput();

        switch (choice)
        {
        case 1:
            // Random Whole
            clearScreen();
            printShuffledLinkedList(head, 1);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 2:
            // Random Voca Only
            clearScreen();
            printShuffledLinkedList(head, 2);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 3:
            // Random Meaning Only
            clearScreen();
            printShuffledLinkedList(head, 3);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 4:
            // Alphabet Whole
            clearScreen();
            printLinkedList(sortedHead, 1);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 5:
            // Alphabet Voca Only
            clearScreen();
            printLinkedList(sortedHead, 2);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 6:
            // Alphabet Meaning Only
            clearScreen();
            printLinkedList(sortedHead, 3);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 7:
            // Custom Whole
            clearScreen();
            printLinkedList(head, 1);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 8:
            // Custom Voca Only
            clearScreen();
            printLinkedList(head, 2);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 9:
            // Custom Meaning Only
            clearScreen();
            printLinkedList(head, 3);
            printf("\nEnter any key to return to menu...");
            getch();
            break;
        case 100:
            // Memory Card game [RANDOM]
            startMemoryCardGame(head, 1);
            break;
        case 101:
            // Memory Card game [ALPHABET]
            startMemoryCardGame(head, 2);
            break;
        case 102:
            // Memory Card game [CUSTOM]
            startMemoryCardGame(head, 3);
            break;
        case 0:
            printf("Exit!\n");
            break;
        default:
            printf("Invalid input. Press any key to try again...\n");
            getch();
            break;
        }
    } while (choice != 0);
}
