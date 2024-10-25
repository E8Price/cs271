/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Ethan Price$
 * [TERM] FALL $2024$
 * 
 ****************************************/
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error! could not open file %s\n", argv[1]);
        return 1;
    }

    parse(file);

    fclose(file);
    return 0;
}



