#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

#ifndef __PARSER_H__
#define __PARSER_H__

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH-2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instr_type{
    invalid = -1,
    a_type,
    c_type
};

typedef struct c_instruction{
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
}c_instruction;




typedef struct a_instruction{
    union instrs{
        hack_addr address;
        char* label;
    }instrs;
    bool is_addr;
}a_instruction;




typedef struct instruction{
    union {
        a_instruction a;
        c_instruction c;
    };
    enum instr_type type;
}instruction;


char *strip(char *s);
int parse(FILE *, instruction *instructions);
char* extract_label(const char*);
bool is_Atype(const char*);
bool is_label(const char*);
bool is_Ctype(const char*);
void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);
void assemble(const char *filename, instruction *instructions, int num_instructions);
opcode instruction_to_opcode(c_instruction instr);


#endif