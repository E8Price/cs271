#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdio.h>

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        exit_program(EXIT_CANNOT_OPEN_FILE, filename);
    }

    parse(file);

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    process_file(argv[1]);
    return 0;
}
