#include <stdarg.h>

#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum exitcode {
    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE = 2 ,
    EXIT_TOO_MANY_INSTRUCTIONS = 3,
    EXIT_INVALID_LABEL = 4,
    EXIT_SYMBOL_ALREADY_EXISTS = 5,
    EXIT_INVALID_A_INSTR = 6
}exitcode;

void exit_program(enum exitcode code, ...);

#endif