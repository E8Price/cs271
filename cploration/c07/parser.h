// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)

typedef uint16_t hack_addr;
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
void parse(char *line, hack_addr *line_number);
void trim_whitespace(char *str);
void remove_comments(char *str);
void remove_carriage_returns(char *str);

#endif // PARSER_H