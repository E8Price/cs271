#include "parser.h"
#include "symtable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    hack_addr line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        remove_carriage_returns(line);
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        remove_comments(line);
        trim_whitespace(line);

        if (line[0] == '\0') {
            continue;
        }

        parse(line, &line_number);
    }

    symtable_print_labels();
    fclose(file);
}

int main(int argc, char *argv[]) {
    symtable_clear();
    insertionCount = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.asm>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        symtable_clear();
        process_file(argv[i]);
    }

    return 0;
}