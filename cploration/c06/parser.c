#include "parser.h"
#include <stdio.h>
#include <string.h>

// Function to check if a line is a label (starts with '(' and ends with ')')
bool is_label(const char *line) {
    size_t len = strlen(line);
    return len > 2 && line[0] == '(' && line[len - 1] == ')';
}

// Function to extract label from a line formatted as (LABEL), removing parentheses
char *extract_label(const char *line, char *label) {
    if (is_label(line)) {
        // Copy the characters between the parentheses
        size_t len = strlen(line);
        strncpy(label, line + 1, len - 2);
        label[len - 2] = '\0'; // Null-terminate the string
    } else {
        label[0] = '\0'; // Empty label if not a valid label line
    }
    return label;
}

// Function to parse a line and determine instruction type
instr_type parse_line(const char *line) {
    if (is_label(line)) {
        return INVALID_INSTRUCTION; // We handle labels separately
    } else if (line[0] == '@') {
        return A_TYPE_INSTRUCTION;
    } else {
        return C_TYPE_INSTRUCTION;
    }
}
