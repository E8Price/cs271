#ifndef HACK_H
#define HACK_H

#include "parser.h"

#define NUM_PREDEFINED_SYMBOLS 23

#define OPCODE_TO_BINARY(opcode)\
(opcode & 0x8000 ? '1' : '0'), \
    (opcode & 0x4000 ? '1' : '0'), \
    (opcode & 0x2000 ? '1' : '0'), \
    (opcode & 0x1000 ? '1' : '0'), \
    (opcode & 0x0800 ? '1' : '0'), \
    (opcode & 0x0400 ? '1' : '0'), \
    (opcode & 0x0200 ? '1' : '0'), \
    (opcode & 0x0100 ? '1' : '0'), \
    (opcode & 0x0080 ? '1' : '0'), \
    (opcode & 0x0040 ? '1' : '0'), \
    (opcode & 0x0020 ? '1' : '0'), \
    (opcode & 0x0010 ? '1' : '0'), \
    (opcode & 0x0008 ? '1' : '0'), \
    (opcode & 0x0004 ? '1' : '0'), \
    (opcode & 0x0002 ? '1' : '0'), \
    (opcode & 0x0001 ? '1' : '0')   
    
typedef enum symbol_id{
    SYM_R0     =     0,
    SYM_R1     =     1,
    SYM_R2     =     2,
    SYM_R3     =     3,
    SYM_R4     =     4,
    SYM_R5     =     5,
    SYM_R6     =     6,
    SYM_R7     =     7,
    SYM_R8     =     8,
    SYM_R9     =     9,
    SYM_R10    =    10,
    SYM_R11    =    11,
    SYM_R12    =    12,
    SYM_R13    =    13,
    SYM_R14    =    14,
    SYM_R15    =    15,
    SYM_SCREEN = 16384,
    SYM_KBD    = 24576,
    SYM_SP     =     0,
    SYM_LCL    =     1,
    SYM_ARG    =     2,
    SYM_THIS   =     3,
    SYM_THAT   =     4
} symbol_id;

typedef struct predefined_symbol{
    char name[10];
    int16_t value;
} predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] ={
    {"R0", SYM_R0},
    {"R1", SYM_R1},
    {"R2", SYM_R2},
    {"R3", SYM_R3},
    {"R4", SYM_R4},
    {"R5", SYM_R5},
    {"R6", SYM_R6},
    {"R7", SYM_R7},
    {"R8", SYM_R8},
    {"R9", SYM_R9},
    {"R10", SYM_R10},
    {"R11", SYM_R11},
    {"R12", SYM_R12},
    {"R13", SYM_R13},
    {"R14", SYM_R14},
    {"R15", SYM_R15},
    {"SCREEN", SYM_SCREEN},
    {"KBD", SYM_KBD},
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT}
};

typedef enum jump_id{
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT  = 1,
    JMP_JEQ  = 2,
    JMP_JGE  = 3,
    JMP_JLT  = 4,
    JMP_JNE  = 5,
    JMP_JLE  = 6,
    JMP_JMP  = 7
} jump_id;

typedef enum dest_id{
    DST_INVALID = -1,
    DST_NULL = 0,
    DST_M    = 1,
    DST_D    = 2,
    DST_MD   = 3,
    DST_A    = 4,
    DST_AM   = 5,
    DST_AD   = 6,
    DST_AMD  = 7
} dest_id;

typedef enum comp_id{
    CMP_INVALID = -1,
    CMP_0 = 42,
    CMP_1 = 63,
    CMP_NEG1 = 58,
    CMP_D = 12,
    CMP_A = 48,
    CMP_NOTD = 13,
    CMP_NOTA = 49,
    CMP_NEGD = 15,
    CMP_NEGA = 51,
    CMP_DPLUS1 = 31,
    CMP_APLUS1 = 55,
    CMP_DMINUS1 = 14,
    CMP_AMINUS1 = 50,
    CMP_DPLUSA = 2,
    CMP_DMINUSA = 19,
    CMP_AMINUSD = 7,
    CMP_DANDA = 0,
    CMP_DORA = 21,
    CMP_M = 112,
    CMP_NOTM = 113,
    CMP_NEGM = 115,
    CMP_MPLUS1 = 119,
    CMP_MMINUS1 = 114,
    CMP_DPLUSM = 66,
    CMP_DMINUSM = 83,
    CMP_MMINUSD = 79,
    CMP_DANDM = 64,
    CMP_DORM = 85
} comp_id;

static inline jump_id str_to_jumpid(const char *s){
    jump_id id = JMP_INVALID;
    if (s == NULL){
        id = JMP_NULL;
    } else if (strcmp(s,"JGT") == 0){
        id = JMP_JGT;
    } else if (strcmp(s,"JEQ") == 0){
        id = JMP_JEQ;
    } else if (strcmp(s,"JGE") == 0){
        id = JMP_JGE;
    } else if (strcmp(s,"JLT") == 0){
        id = JMP_JLT;
    } else if (strcmp(s,"JNE") == 0){
        id = JMP_JNE;
    } else if (strcmp(s,"JLE") == 0){
        id = JMP_JLE;
    } else if (strcmp(s,"JMP") == 0){
        id = JMP_JMP;
    }
    return id;
};

static inline dest_id str_to_destid(const char *s){
    dest_id id = DST_INVALID;
    if (s == NULL){
        id = DST_INVALID;
    } else if (strcmp(s,"0") == 0){
        id = DST_NULL;
    } else if (strcmp(s,"M") == 0){
        id = DST_M;
    } else if (strcmp(s,"D") == 0){
        id = DST_D;
    } else if (strcmp(s,"MD") == 0){
        id = DST_MD;
    } else if (strcmp(s,"A") == 0){
        id = DST_A;
    } else if (strcmp(s,"AM") == 0){
        id = DST_AM;
    } else if (strcmp(s,"AD") == 0){
        id = DST_AD;
    } else if (strcmp(s,"AMD") == 0){
        id = DST_AMD;
    }
    return id;
};

static inline comp_id str_to_compid(const char *s, int *a){
    comp_id id = CMP_INVALID;
    *a = 0;
    if (s == NULL){
        id = CMP_INVALID;
    } else if (strcmp(s,"0") == 0){
        id = CMP_0;
    } else if (strcmp(s,"1") == 0){
        id = CMP_1;
    } else if (strcmp(s,"-1") == 0){
        id = CMP_NEG1;
    } else if (strcmp(s,"D") == 0){
        id = CMP_D;
    } else if (strcmp(s,"A") == 0){
        id = CMP_A;
    } else if (strcmp(s,"!D") == 0){
        id = CMP_NOTD;
    } else if (strcmp(s,"!A") == 0){
        id = CMP_NOTA;
    } else if (strcmp(s,"-D") == 0){
        id = CMP_NEGD;
    } else if (strcmp(s,"-A") == 0){
        id = CMP_NEGA;
    } else if (strcmp(s,"D+1") == 0){
        id = CMP_DPLUS1;
    } else if (strcmp(s,"A+1") == 0){
        id = CMP_APLUS1;
    } else if (strcmp(s,"D-1") == 0){
        id = CMP_DMINUS1;
    } else if (strcmp(s,"A-1") == 0){
        id = CMP_AMINUS1;
    } else if (strcmp(s,"D+A") == 0){
        id = CMP_DPLUSA;
    } else if (strcmp(s,"D-A") == 0){
        id = CMP_DMINUSA;
    } else if (strcmp(s,"A-D") == 0){
        id = CMP_AMINUSD;
    } else if (strcmp(s,"D&A") == 0){
        id = CMP_DANDA;
    } else if (strcmp(s,"D|A") == 0){
        id = CMP_DORA;
    } else if (strcmp(s,"M") == 0){
        id = CMP_M;
        id = CMP_A;
        *a = 1;
    } else if (strcmp(s,"!M") == 0){
        id = CMP_NOTM;
        id = CMP_NOTA;
        *a = 1;
    } else if (strcmp(s,"-M") == 0){
        id = CMP_NEGM;
        id = CMP_NEGA;
        *a = 1;
    } else if (strcmp(s,"M+1") == 0){
        id = CMP_MPLUS1;
        id = CMP_APLUS1;
        *a = 1;
    } else if (strcmp(s,"M-1") == 0){
        id = CMP_MMINUS1;
        id = CMP_AMINUS1;
        *a = 1;
    } else if (strcmp(s,"D+M") == 0){
        id = CMP_DPLUSM;
        id = CMP_DPLUSA;
        *a = 1;
    } else if (strcmp(s,"D-M") == 0){
        id = CMP_DMINUSM;
        id = CMP_DMINUSA;
        *a = 1;
    } else if (strcmp(s,"M-D") == 0){
        id = CMP_MMINUSD;
        id = CMP_AMINUSD;
        *a = 1;
    } else if (strcmp(s,"D&M") == 0){
        id = CMP_DANDM;
        id = CMP_DANDA;
        *a = 1;
    } else if (strcmp(s,"D|M") == 0){
        id = CMP_DORM;
        id = CMP_DORA;
        *a = 1;
    };
    return id;
}
#endif