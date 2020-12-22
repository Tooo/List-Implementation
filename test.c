#include "list.h"
#include <stdio.h>
#include <stdlib.h>

static int * array;

void printResult(int result) {
    if (result == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL in %d\n", result);
    }
}

void createFilledArray() {
    array = malloc(LIST_MAX_NUM_NODES * sizeof(int));

    for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
        array[i] = i;
    }
}

// Free item test function
void freeTest(void * item) {
    //int * num = item;
    //printf("Bye %d", * num);
}

int createOverList() {
    int result = 0;
    List * listArray[LIST_MAX_NUM_HEADS+1];

    for (int i = 0; i < LIST_MAX_NUM_HEADS+1; i++) {
        listArray[i] = List_create();
    }

    if (listArray[LIST_MAX_NUM_HEADS]) {
        result = 1;
    }

    for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        List_free(listArray[i], freeTest);
    }

    return result;
}

int createCount() {
    int result = 0;
    List * list = List_create();

    if (List_count(list)) {
        result = 1;
    }

    List_free(list, freeTest);

    return result;
}

typedef int (*NEWNODE_FN) (List * list, void* pItem);
int loopOverNodes(NEWNODE_FN pListFunction) {
    int result = 1;
    List * list = List_create();

    for (int i = 0; i < LIST_MAX_NUM_NODES; i++) {
        (pListFunction)(list, &array[i]);
    }

    if ((pListFunction)(list, &array[0]) == LIST_FAIL) {
        result = 0;
    }

    List_free(list, freeTest);
    return result;
}

int oneNode(NEWNODE_FN pListFunction) {
    int result = 0;
    List * list = List_create();

    if ((pListFunction)(list, &array[0]) == LIST_FAIL) {
        result = 1;
    }

    if (List_count(list) != 1) {
        result = 2;
    }

    if (List_first(list) != List_last(list)) {
        result = 3;
    }

    if (List_curr(list) != &array[0]) {
        result = 4;
    }

    // Before head
    if (List_prev(list) != NULL || List_curr(list) != NULL) {
        result = 5;
    }

    if (List_next(list) != &array[0] || List_curr(list) != &array[0]) {
        result = 6;
    }

    // After tail
    if (List_next(list) != NULL || List_curr(list) != NULL) {
        result = 7;
    }

    if (List_prev(list) != &array[0] || List_curr(list) != &array[0]) {
        result = 8;
    }

    List_free(list, freeTest);
    return result;
}

int fourNodes(NEWNODE_FN pListFunction, int * order) {
    int result = 0;
    List * list = List_create();

    if ((pListFunction)(list, &array[order[0]]) == LIST_FAIL) {
        result = 1;
    }

    if (List_prev(list) != NULL) {
        result = 2;
    }

    // Before head
    if ((pListFunction)(list, &array[order[1]]) == LIST_FAIL) {
        result = 3;
    }

    List_next(list);

    if (List_next(list) != NULL) {
        result = 4;
    }

    //Beyond tail
    if ((pListFunction)(list, &array[order[2]]) == LIST_FAIL) {
        result = 5;
    }

    if (List_first(list) == NULL) {
        result = 6;
    }
    
    if (List_next(list) == NULL) {
        result = 7;
    }

    //Middle
    if ((pListFunction)(list, &array[order[3]]) == LIST_FAIL) {
        result = 8;
    }

    if (List_count(list) != 4) {
        result = 9;
    }

    // Compare to array
    if (List_first(list) != &array[0]) {
        result = 10;
    }

    if (List_next(list) != &array[1]) {
        result = 11;
    }

    if (List_next(list) != &array[2]) {
        result = 12;
    }

    if (List_next(list) != &array[3]) {
        result = 13;
    }

    if (List_last(list) != &array[3]) {
        result = 14;
    }

    if (List_prev(list) != &array[2]) {
        result = 15;
    }

    if (List_prev(list) != &array[1]) {
        result = 16;
    }

    if (List_prev(list) != &array[0]) {
        result = 17;
    }

    List_free(list, freeTest);
    return result;
}

typedef void * (*DELETENODE_FN) (List * list);
int deleteEmpty(DELETENODE_FN pListFunction) {
    int result = 0;
    List * list = List_create();

    if ((pListFunction)(list) != NULL) {
        result = 1;
    }

    if (List_count(list) != 0) {
        result = 2;
    }

    List_free(list, freeTest);
    return result;
}

int removeOne() {
    int result = 0;
    List * list = List_create();

    List_append(list, &array[0]);

    List_prev(list);
    
    if (List_remove(list) != NULL) {
        result = 1;
    }

    List_next(list);
    List_next(list);

    if (List_remove(list) != NULL) {
        result = 2;
    }

    if (List_first(list) != &array[0]) {
        result = 3;
    }

    if (List_remove(list) != &array[0]) {
        result = 4;
    }
    
    if (List_count(list) != 0) {
        result = 5;
    }

    List_free(list, freeTest);
    return result;
}

int removeThree() {
    int result = 0;
    List * list = List_create();

    for (int i = 0; i < 3; i++) {
        List_append(list, &array[i]);
    }

    // Remove Head
    List_first(list);
    if (List_remove(list) != &array[0]) {
        result = 1;
    }

    if (List_curr(list) != List_first(list) || List_curr(list) != &array[1]) {
        result = 2;
    }

    if (List_count(list) != 2) {
        result = 3;
    }

    List_prepend(list, &array[0]);

    //Remove Tail
    List_last(list);
    if (List_remove(list) != &array[2]) {
        result = 4;
    }

    if (List_curr(list) != NULL) {
        result = 5;
    }

    if (List_prev(list) != List_last(list) || List_curr(list) != &array[1]) {
        result = 6;
    }

    if (List_count(list) != 2) {
        result = 7;
    }

    List_append(list, &array[2]);

    //Remove Middle
    List_prev(list);

    if (List_remove(list) != &array[1]) {
        result = 8;
    }

    if (List_curr(list) != &array[2]) {
        result = 9;
    }

    if (List_prev(list) != List_first(list) || List_curr(list) != &array[0]) {
        result = 10;
    }

    if (List_next(list) != List_last(list) || List_curr(list) != &array[2]) {
        result = 11;
    }

    if (List_count(list) != 2) {
        result = 12;
    }

    List_free(list, freeTest);
    return result;
}

int concatEmptyEmpty () {
    int result = 0;
    List * list1 = List_create();
    List * list2 = List_create();

    List_concat(list1, list2);

    if (List_count(list1) != 0) {
        result = 1;
    }

    if (List_curr(list1) != NULL) {
        result = 2;
    }

    if (List_curr(list1) != List_first(list1) || List_curr(list1) != List_last(list1)) {
        result = 3;
    }

    List_free(list1, freeTest);
    return result;    
}

int concatFilledEmpty () {
    int result = 0;
    List * list1 = List_create();
    List * list2 = List_create();

    List_append(list1, &array[0]);

    List_concat(list1, list2);

    if (List_count(list1) != 1) {
        result = 1;
    }

    if (List_curr(list1) != &array[0]) {
        result = 2;
    }

    if (List_curr(list1) != List_first(list1) || List_curr(list1) != List_last(list1)) {
        result = 3;
    }

    List_free(list1, freeTest);
    return result;    
}

int concatEmptyFilled () {
    int result = 0;
    List * list1 = List_create();
    List * list2 = List_create();

    List_append(list2, &array[0]);

    List_concat(list1, list2);

    if (List_count(list1) != 1) {
        result = 1;
    }

    if (List_curr(list1) != NULL) {
        result = 2;
    }

    if (List_first(list1) != &array[0]) {
        result = 3;
    }

    if (List_curr(list1) != List_last(list1) ) {
        result = 4;
    }

    List_free(list1, freeTest);
    return result;    
}

int concatFilledFilled () {
    int result = 0;
    List * list1 = List_create();
    List * list2 = List_create();

    List_append(list1, &array[0]);
    List_append(list2, &array[1]);

    List_concat(list1, list2);

    if (List_count(list1) != 2) {
        result = 1;
    }

    if (List_curr(list1) != &array[0]) {
        result = 2;
    }

    if (List_curr(list1) != List_first(list1)) {
        result = 3;
    }

    if (List_next(list1) != List_last(list1)) {
        result = 4;
    }

    if (List_curr(list1) != &array[1]) {
        result = 5;
    }

    if (List_prev(list1) != &array[0]) {
        result = 6;
    }

    List_free(list1, freeTest);
    return result;    
}

void freePass(void * item) {
    int * numPtr = item;
    int num = *numPtr;

    if (num == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

void freeOne() {
    List * list = List_create();

    List_append(list, &array[0]);

    List_free(list, freePass);
}

int trimOne () {
    int result = 0;
    List * list = List_create();

    List_append(list, &array[0]);

    if (List_trim(list) != &array[0]) {
        result = 1;
    } 

    if (List_count(list) != 0) {
        result = 2;
    }

    List_free(list, freeTest);
    return result;
}

int trimTwo() {
    int result = 0;
    List * list = List_create();

    List_append(list, &array[0]);
    List_append(list, &array[1]);

    if (List_trim(list) != &array[1]) {
        result = 1;
    }

    if (List_count(list) != 1) {
        result = 2;
    }

    if (List_curr(list) != List_last(list) || List_last(list) != List_first(list)) {
        result = 3;
    }

    if (List_curr(list) != &array[0]) {
        result = 4;
    }

    List_free(list, freeTest);
    return result;
}

bool comparator(void * item, void * item2) {
    int * numPtr = item;
    int * numPtr2 = item2;
    int num = *numPtr;
    int num2 = *numPtr2;

    return num == num2;
}

int searchTests() {
    int result = 0;
    List * list = List_create();

    for (int i = 0; i < 10; i++) {
        List_append(list, &array[i]);
    }

    if (List_search(list, comparator, &array[0]) != NULL) {
        result = 1;
    }

    if (List_search(list, comparator, &array[9]) != NULL) {
        result = 2;
    }

    List_first(list);

    if (List_search(list, comparator, &array[0]) != &array[0]) {
        result = 3;
    }

    if (List_curr(list) != List_first(list)) {
        result = 4;
    }

    List_prev(list);

    if (List_search(list, comparator, &array[1]) != &array[1]) {
        result = 5;
    }

    if (List_search(list, comparator, &array[10]) != NULL) {
        result = 6;
    }

    List_free(list, freeTest);
    return result;
}

int main () {
    createFilledArray();

    printf("---List_create test---\n");

    printf("Create more than max lists: ");
    printResult(createOverList());

    printf("Intial count: ");
    printResult(createCount());

    printf("\n---List_add test---\n");
    int addOrder[4] = {1, 0, 3, 2};

    printf("Add more than max nodes: ");
    printResult(loopOverNodes(List_add));

    printf("1 node tests: ");
    printResult(oneNode(List_add));

    printf("4 node tests: ");
    printResult(fourNodes(List_add, addOrder));

    printf("\n---List_insert test---\n");
    int insertOrder[4] = {2, 0, 3, 1};

    printf("Insert more than max nodes: ");
    printResult(loopOverNodes(List_insert));

    printf("1 node tests: ");
    printResult(oneNode(List_insert));

    printf("4 node tests: ");
    printResult(fourNodes(List_insert, insertOrder));

    printf("\n---List_append test---\n");
    int appendOrder[4] = {0, 1, 2, 3};

    printf("Append more than max nodes: ");
    printResult(loopOverNodes(List_append));

    printf("1 node tests: ");
    printResult(oneNode(List_append));

    printf("4 node tests: ");
    printResult(fourNodes(List_append, appendOrder));

    printf("\n---List_prepend test---\n");
    int prependOrder[4] = {3, 2, 1, 0};

    printf("Prepend more than max nodes: ");
    printResult(loopOverNodes(List_prepend));

    printf("1 node tests: ");
    printResult(oneNode(List_prepend));

    printf("4 node tests: ");
    printResult(fourNodes(List_prepend, prependOrder));

    printf("\n---List_remove test---\n");

    printf("Remove empty list: ");
    printResult(deleteEmpty(List_remove));

    printf("1 node tests: ");
    printResult(removeOne());

    printf("3 nodes tests: ");
    printResult(removeThree());

    printf("\n---List_concat test---\n");

    printf("Empty Empty test: ");
    printResult(concatEmptyEmpty());

    printf("Filled Empty test: ");
    printResult(concatFilledEmpty());

    printf("Empty Filled test: ");
    printResult(concatEmptyFilled());

    printf("Filled Filled test: ");
    printResult(concatEmptyFilled());

    printf("\n---List_free test---\n");

    printf("Free 1 node test: ");
    freeOne();

    printf("\n---List_trim test---\n");

    printf("Trim empty list: ");
    printResult(deleteEmpty(List_trim));

    printf("1 node tests: ");
    printResult(trimOne());

    printf("2 node tests: ");
    printResult(trimTwo());

    printf("\n---List_search test---\n");

    printf("Many search tests: ");
    printResult(searchTests());

    free(array);
}