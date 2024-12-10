#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_label(const char *line) {
    return line[0] == '(' && line[strlen(line) - 1] == ')';
}

char *extract_label(const char *line, char *label) {
    if (is_label(line)) {
        strncpy(label, line + 1, strlen(line) - 2); // Extract label without parentheses
        label[strlen(line) - 2] = '\0';
    }
    return label;
}

instr_type parse_line(const char *line) {
    if (line[0] == '@') {
        return A_TYPE_INSTRUCTION;
    }
    return C_TYPE_INSTRUCTION;
}

void parse(FILE *file) {
    char line[MAX_LINE_LENGTH];
    unsigned int line_num = 0, instr_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0; // Remove newline characters
        line_num++;

        if (line[0] == '\0' || (line[0] == '/' && line[1] == '/')) {
            continue; // Skip comments and blank lines
        }

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }

        if (is_label(line)) {
            char label[MAX_LABEL_LENGTH];
            extract_label(line, label);

            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, line);
            }

            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
            }

            symtable_insert(label, instr_num);
            continue;
        }

        instr_type type = parse_line(line);
        printf("%u: %c  %s\n", instr_num, (type == A_TYPE_INSTRUCTION ? 'A' : 'C'), line);

        if (type != INVALID_INSTRUCTION) {
            instr_num++;
        }
    }
}
