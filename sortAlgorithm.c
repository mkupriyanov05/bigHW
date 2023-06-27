#include "sortAlgorithm.h"
#include "menuFile.h"
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)


bool compareIntegers(void *firstInteger, void *secondInteger) {
    if (*(int*)firstInteger <= *(int*)secondInteger)
        return true;
    return false;
}

bool compareDoubles(void *firstFloat, void *secondFloat) {
    if (*(double*)firstFloat <= *(double*)secondFloat)
        return true;
    return false;
}

bool compareStrings(void *firstString, void *secondString) {
    if (strcmp(*(char**)firstString, *(char**)secondString) <= 0)
        return true;
    return false;
}


static int partition(Book_t *database, int low, int high, bool (*compare)(void*, void*), size_t offset);

void quickSort(Book_t *database, int low, int high, bool (*compare)(void*, void*), size_t offset) {
    if (low >= high)
        return;

    int pi = partition(database, low, high, compare, offset);
    quickSort(database, low, pi - 1, compare, offset);
    quickSort(database, pi + 1, high, compare, offset);
}

static int partition(Book_t *database, int low, int high, bool (*compare)(void*, void*), size_t offset) {
    void *pivot = (void*)&database[high] + offset;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare((void*)&database[j] + offset, pivot)) {
            i++;
            SWAP(database[i], database[j]);
        }
    }
    SWAP(database[i + 1], database[high]);
    return i + 1;
}
