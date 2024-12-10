#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "symtable.h"
#include "error.h"

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef enum {
    INVALID_INSTRUCTION = -1,
    A_TYPE_INSTRUCTION,
    C_TYPE_INSTRUCTION
} instr_type;

typedef struct {
    opcode a : 1;
    opcode comp : 7;
    opcode dest : 3;
    opcode jump : 3;
} c_instruction;

typedef struct {
    union {
        hack_addr address;
        char *label;
    };
    bool is_addr;
} a_instruction;

typedef struct {
    union {
        a_instruction a_instr;
        c_instruction c_instr;
    };
    instr_type type;
} instruction;

bool is_label(const char *line);
char *extract_label(const char *line, char *label);
instr_type parse_line(const char *line);

#endif // __PARSER_H__
