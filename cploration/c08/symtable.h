#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

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
void symtable_print_labels();

#endif // __SYMTABLE_H__
