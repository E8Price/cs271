#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE] = { NULL };
Symbol* insertionOrder[SYMBOL_TABLE_SIZE] = { NULL };
int insertionCount = 0;

int hash(char *str) {
    if (!str) return 0;
    
    unsigned long hash = 5381;
    int c;
    
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return (int)(hash % SYMBOL_TABLE_SIZE);
}

Symbol *symtable_find(char *key) {
    if (!key) return NULL;
    
    int hashIndex = hash(key);
    int originalIndex = hashIndex;
    
    while (hashArray[hashIndex] != NULL) {
        if (strcmp(hashArray[hashIndex]->name, key) == 0) {
            return hashArray[hashIndex];
        }
        
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
        if (hashIndex == originalIndex) break;
    }
    
    return NULL;
}

void symtable_insert(char *key, hack_addr addr) {
    if (!key) return;
    
    if (symtable_find(key) != NULL) {
        return;
    }

    Symbol *item = (Symbol*)malloc(sizeof(Symbol));
    if (!item) return;
    
    item->name = strdup(key);
    if (!item->name) {
        free(item);
        return;
    }
    item->addr = addr;

    int hashIndex = hash(key);
    while (hashArray[hashIndex] != NULL) {
        hashIndex = (hashIndex + 1) % SYMBOL_TABLE_SIZE;
    }
    
    hashArray[hashIndex] = item;
    insertionOrder[insertionCount++] = item;
}

// Compare function for qsort
static int compare_symbols(const void *a, const void *b) {
    Symbol *const *sym1 = a;
    Symbol *const *sym2 = b;
    
    // First compare by address
    if ((*sym1)->addr != (*sym2)->addr) {
        return (*sym1)->addr - (*sym2)->addr;
    }
    
    // If addresses are equal, maintain stable sort by using original order
    for (int i = 0; i < insertionCount; i++) {
        if (insertionOrder[i] == *sym1) return -1;
        if (insertionOrder[i] == *sym2) return 1;
    }
    return 0;
}

void symtable_print_labels(void) {
    // Create a temporary array for sorting
    Symbol** sortedSymbols = malloc(insertionCount * sizeof(Symbol*));
    if (!sortedSymbols) return;
    
    // Copy symbols to temporary array
    for (int i = 0; i < insertionCount; i++) {
        sortedSymbols[i] = insertionOrder[i];
    }
    
    // Sort the temporary array
    qsort(sortedSymbols, insertionCount, sizeof(Symbol*), compare_symbols);
    
    // Print sorted symbols
    for (int i = 0; i < insertionCount; i++) {
        printf("{(%s),%d}\n", sortedSymbols[i]->name, sortedSymbols[i]->addr);
    }
    
    free(sortedSymbols);
}

void symtable_clear(void) {
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if (hashArray[i] != NULL) {
            free(hashArray[i]->name);
            free(hashArray[i]);
            hashArray[i] = NULL;
        }
    }

    for (int i = 0; i < insertionCount; i++) {
        insertionOrder[i] = NULL;
    }
    
    insertionCount = 0;
}