#pragma once

int reviewCompleted;

void startMemoryCardGame(LinkedList* head, const int mode);

LinkedList* memoryCardRecursion(const int mode, const int count, int remaining,
    LinkedList** nodes, LinkedList* current, LinkedList* reviewListHead, LinkedList* reviewListTail);

const int countReviewList(LinkedList* reviewListHead);

void checkIfReview(LinkedList* reviewListHead, const int mode);
