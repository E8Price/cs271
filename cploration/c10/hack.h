#include <stdarg.h>

#ifndef __HACK_H__
#define __HACK_H__

#define NUM_PREDEFINED_SYMBOLS 23
typedef int16_t address;

typedef enum symbol_id {
    SYM_SP = 0,
    SYM_LCL = 1,
    SYM_ARG = 2,
    SYM_THIS = 3,
    SYM_THAT = 4,
    SYM_R0 = 0,
    SYM_R1 = 1,
    SYM_R2 = 2,
    SYM_R3 = 3,
    SYM_R4 = 4,
    SYM_R5 = 5,
    SYM_R6 = 6,
    SYM_R7 = 7,
    SYM_R8 = 8,
    SYM_R9 = 9,
    SYM_R10 = 10,
    SYM_R11 = 11,
    SYM_R12 = 12,
    SYM_R13 = 13,
    SYM_R14 = 14,
    SYM_R15 = 15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576
}symbol_id;

typedef struct predefined_symbol {
    char *name;
    int16_t address;
}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
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
    {"SP", SYM_SP},
    {"LCL", SYM_LCL},
    {"ARG", SYM_ARG},
    {"THIS", SYM_THIS},
    {"THAT", SYM_THAT},
    {"KBD", SYM_KBD},
    {"SCREEN", SYM_SCREEN},
};

typedef enum jump_id {
    JMP_INVALID = -1,
    JMP_NULL = 0,
    JMP_JGT = 1,
    JMP_JEQ = 2,
    JMP_JGE = 3,
    JMP_JLT = 4,
    JMP_JNE = 5,
    JMP_JLE = 6,
    JMP_JMP = 7
}jump_id;

typedef enum dest_id{
    DEST_INVALID = -1,
    DEST_NULL = 0,
    DEST_M = 1,
    DEST_D = 2,
    DEST_DM = 3,
    DEST_A = 4,
    DEST_AM = 5,
    DEST_AD = 6,
    DEST_ADM = 7
}dest_id;

typedef enum comp_id{
    //a == 0;
    COMP_INVALID = -1,
    COMP_0 = 42,
    COMP_1 = 63,
    COMP_NEG1 = 58,
    COMP_D = 12,
    COMP_A = 48,
    COMP_NOTD = 13,
    COMP_NOTA = 49,
    COMP_NEGD = 15,
    COMP_NEGA = 51,
    COMP_DPLUS1 = 31,
    COMP_APLUS1 = 55,
    COMP_DMINUS1 = 14,
    COMP_AMINUS1 = 50,
    COMP_DPLUSA = 2,
    COMP_DMINUSA = 19,
    COMP_AMINUSD = 7,
    COMP_DANDA = 0,
    COMP_DORA = 21,
    //a == 1;
    COMP_M = 48,
    COMP_NOTM = 49,
    COMP_NEGM = 51,
    COMP_MPLUS1 = 55,
    COMP_MMINUS1 = 50,
    COMP_DPLUSM = 2,
    COMP_DMINUSM = 19,
    COMP_MMINUSD = 7,
    COMP_DANDM = 0,
    COMP_DORM = 21
}comp_id;

static inline jump_id str_to_jumpid(const char *s){
    jump_id id = JMP_INVALID;
    
    if (s == NULL) {
        id = JMP_NULL;
    } else if (!strcmp(s, "JGT")) {
        id = JMP_JGT;
    } else if (!strcmp(s, "JEQ")) {
        id = JMP_JEQ;
    } else if (!strcmp(s, "JGE")) {
        id = JMP_JGE;
    } else if (!strcmp(s, "JLT")) {
        id = JMP_JLT;
    } else if (!strcmp(s, "JNE")) {
        id = JMP_JNE;
    }else if (!strcmp(s, "JLE")) {
        id = JMP_JLE;
    }else if (!strcmp(s, "JMP")) {
        id = JMP_JMP;
    }
    return id;
}

static inline dest_id str_to_destid(const char *s){
    dest_id id = DEST_INVALID;
    
    if(s == NULL){
        id = DEST_NULL;
    } else if (!strcmp(s, "M")) {
        id = DEST_M;
    }else if (!strcmp(s, "D")) {
        id = DEST_D;
    }else if (!strcmp(s, "MD")) {
        id = DEST_DM;
    }else if (!strcmp(s, "A")) {
        id = DEST_A;
    }else if (!strcmp(s, "AM")) {
        id = DEST_AM;
    }else if (!strcmp(s, "AD")) {
        id = DEST_AD;
    }else if (!strcmp(s, "AMD")) {
        id = DEST_ADM;
    }else if (!strcmp(s, "DM")){
        id = DEST_DM;
    }
    return id;
}


static inline comp_id str_to_compid(const char *s, int *a){
    comp_id  id = COMP_INVALID;
    
        if(!strcmp(s, "0")){
            id = COMP_0;
        }else if(!strcmp(s, "1")){
            id  = COMP_1;
        } else if(!strcmp(s, "-1")){
            id  = COMP_NEG1;
        } else if(!strcmp(s, "D")){
            id  = COMP_D;
        } else if(!strcmp(s, "A")){
            id  = COMP_A;
        } else if(!strcmp(s, "!D")){
            id  = COMP_NOTD;
        } else if(!strcmp(s, "!A")){
            id  = COMP_NOTA;
        } else if(!strcmp(s, "-D")){
            id  = COMP_NEGD;
        } else if(!strcmp(s, "-A")){
            id  = COMP_NEGA;
        } else if(!strcmp(s, "D+1")){
            id  = COMP_DPLUS1;
        }  else if(!strcmp(s, "A+1")){
            id  = COMP_APLUS1;
        }  else if(!strcmp(s, "D-1")){
            id  = COMP_DMINUS1;
        } else if(!strcmp(s, "A-1")){
            id  = COMP_AMINUS1;
        } else if(!strcmp(s, "D+A")){
            id  = COMP_DPLUSA;
        } else if(!strcmp(s, "D-A")){
            id  = COMP_DMINUSA;
        } else if(!strcmp(s, "A-D")){
            id  = COMP_AMINUSD;
        } else if(!strcmp(s, "D&A")){
            id  = COMP_DANDA;
        } else if(!strcmp(s, "D|A")){
            id  = COMP_DORA;
        } else if(!strcmp(s, "M")){
            *a = 1;
            id  = COMP_M;
        }  else if(!strcmp(s, "!M")){
            *a = 1;
            id  = COMP_NOTM;
        }  else if(!strcmp(s, "-M")){
            *a = 1;
            id  = COMP_NEGM;
        } else if(!strcmp(s, "M+1")){
            *a = 1;
            id  = COMP_MPLUS1;
        } else if(!strcmp(s, "M-1")){
            *a = 1;
            id  = COMP_MMINUS1;
        } else if(!strcmp(s, "D+M")){
            *a = 1;
            id  = COMP_DPLUSM;
        } else if(!strcmp(s, "D-M")){
            *a = 1;
            id  = COMP_DMINUSM;
        } else if(!strcmp(s, "M-D")){
            *a = 1;
            id  = COMP_MMINUSD;
        } else if(!strcmp(s, "D&M")){
            *a = 1;
            id  = COMP_DANDM;
        } else if(!strcmp(s, "D|M")){
            *a = 1;
            id  = COMP_DORM;
        }
    return id;
}


#endif