// symtable.h
#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SYMBOL_TABLE_SIZE 1000

typedef uint16_t hack_addr;

typedef struct {
    char *name;
    hack_addr addr;
} Symbol;

extern Symbol* hashArray[SYMBOL_TABLE_SIZE];
extern Symbol* insertionOrder[SYMBOL_TABLE_SIZE];
extern int insertionCount;

int hash(char *str);
Symbol *symtable_find(char *key);
void symtable_insert(char *key, hack_addr addr);
void symtable_print_labels(void);
void symtable_clear(void);

#endif // SYMTABLE_H