#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "symtable.h"


typedef int16_t hack_addr;

struct Symbol *hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return (hash % SYMBOL_TABLE_SIZE);
}

struct Symbol *symtable_find(char * name) {
   int hashIndex = hash(name);
    
   while(hashArray[hashIndex] != NULL) {
    
      if((strcmp(hashArray[hashIndex]->name, name)) == 0)
         return hashArray[hashIndex];
            
      ++hashIndex;
        
      hashIndex = (hashIndex % SYMBOL_TABLE_SIZE);
   }
    
   return NULL;
}

void symtable_insert(char* name, hack_addr addr){
    struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
    item->name = (char*)malloc(strlen(name) + 1);
    strcpy(item->name, name);
    item->addr = addr;
    
    int hashIndex  = hash(name);
    
       while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      
          ++hashIndex;
            
          hashIndex = (hashIndex % SYMBOL_TABLE_SIZE);
       }
    
    hashArray[hashIndex] = item;
}

void symtable_print_labels() {
   int i = 0;
   for(i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
}