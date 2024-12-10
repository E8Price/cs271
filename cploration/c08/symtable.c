#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE] = { NULL };
Symbol* insertionOrder[SYMBOL_TABLE_SIZE] = { NULL };
int insertionCount = 0;

int hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return (int)(hash % SYMBOL_TABLE_SIZE);
}

Symbol *symtable_find(char *key) {
    int hashIndex = hash(key);
    int originalIndex = hashIndex;

    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, key) == 0) {
            return hashArray[hashIndex];
        }

        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
        if (hashIndex == originalIndex) {
            break;
        }
    }
    return NULL;
}

void symtable_insert(char *key, hack_addr addr) {
    Symbol *item = malloc(sizeof(Symbol));
    item->name = strdup(key);
    item->addr = addr;

    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }

    hashArray[hashIndex] = item;
    insertionOrder[insertionCount++] = item;
}

void symtable_print_labels(void) {
    for (int i = 0; i < insertionCount; i++) {
        printf("{(%s),%d}\n", insertionOrder[i]->name, insertionOrder[i]->addr);
    }
}
