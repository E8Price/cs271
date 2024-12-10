#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef __PARSER_H__
#define __PARSER_H__

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH  (MAX_LINE_LENGTH-2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;




typedef enum instr_type {
    Invalid = -1,
    A_type,
    C_type,
}instr_type;

typedef struct c_instruction{
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
}c_instruction;



typedef struct a_instruction{
    union {
        hack_addr address;
        char* label;
    }operand;
    bool is_addr;
}a_instruction;



typedef struct instruction{
   union {
        a_instruction a;
        c_instruction c;
    }instr;
    enum instr_type sometype;
}instruction;

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
bool parse_A_instruction(const char *line, a_instruction *instr);
char *extract_label(const char *line, char* label);
char *strip(char *s);

int parse(FILE * file, instruction *instructions);
void add_predefined_symbols();
void parse_C_instruction(char *line, c_instruction *instr);



#endif