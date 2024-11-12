#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to remove inline comments starting with "//"
void strip_inline_comment(char *line) {
    char *comment_start = strstr(line, "//");
    if (comment_start) {
        *comment_start = '\0';  // Terminate the string before the comment
    }
}

// Function to trim leading and trailing whitespace
void trim_whitespace(char *line) {
    char *start = line;

    // Trim leading whitespace
    while (isspace((unsigned char)*start)) {
        start++;
    }

    // Trim trailing whitespace
    char *end = start + strlen(start) - 1;
    while (end >= start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    // Move the trimmed string back to the original buffer
    memmove(line, start, strlen(start) + 1);
}

// Function to reduce multiple internal spaces to a single space
void reduce_internal_spaces(char *line) {
    char *src = line;
    char *dst = line;
    bool in_word = false;

    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            // If we're at the start of a word, and it's not the first word, add a space
            if (!in_word && dst != line) {
                *dst++ = ' ';
            }
            *dst++ = *src;
            in_word = true;
        } else {
            in_word = false;
        }
        src++;
    }
    *dst = '\0';
}

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Remove newline characters
        line[strcspn(line, "\r\n")] = '\0';

        // Remove any inline comments
        strip_inline_comment(line);

        // Trim leading and trailing whitespace
        trim_whitespace(line);

        // Skip empty lines
        if (line[0] == '\0') {
            continue;
        }

        // Reduce internal spaces to a single space
        reduce_internal_spaces(line);

        instr_type type = parse_line(line);

        switch (type) {
            case A_TYPE_INSTRUCTION:
                printf("A  %s\n", line);  // Two spaces after 'A'
                break;
            case C_TYPE_INSTRUCTION:
                printf("C  %s\n", line);  // Two spaces after 'C'
                break;
            case INVALID_INSTRUCTION:
                if (is_label(line)) {
                    extract_label(line, label);
                    printf("L  %s\n", label);  // Two spaces after 'L', label without parentheses
                } else {
                    printf("Invalid instruction: %s\n", line);
                }
                break;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.asm>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        process_file(argv[i]);
    }

    return 0;
}
