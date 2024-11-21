// parser.c
#include "parser.h"
#include "symtable.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_whitespace(char *str) {
    if (!str) return;
    
    char *start = str;
    char *end;

    while (isspace((unsigned char)*start)) start++;

    if (*start == 0) {
        *str = '\0';
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}

void remove_comments(char *str) {
    char *comment = strstr(str, "//");
    if (comment) {
        *comment = '\0';
    }
}

void remove_carriage_returns(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '\r') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

bool is_label(const char *line) {
    if (!line) return false;
    
    char temp[MAX_LINE_LENGTH];
    strncpy(temp, line, MAX_LINE_LENGTH - 1);
    temp[MAX_LINE_LENGTH - 1] = '\0';
    
    trim_whitespace(temp);
    size_t len = strlen(temp);
    
    return (len > 2 && temp[0] == '(' && temp[len - 1] == ')');
}

char *extract_label(const char *line, char *label) {
    if (!line || !label || !is_label(line)) {
        if (label) label[0] = '\0';
        return label;
    }

    char temp[MAX_LINE_LENGTH];
    strncpy(temp, line, MAX_LINE_LENGTH - 1);
    temp[MAX_LINE_LENGTH - 1] = '\0';
    trim_whitespace(temp);

    const char *start = strchr(temp, '(');
    const char *end = strrchr(temp, ')');

    if (start && end && end > start) {
        size_t label_len = end - start - 1;
        strncpy(label, start + 1, label_len);
        label[label_len] = '\0';
    } else {
        label[0] = '\0';
    }
    
    return label;
}

instr_type parse_line(const char *line) {
    if (!line) return INVALID_INSTRUCTION;
    
    if (is_label(line)) {
        return INVALID_INSTRUCTION;
    }
    if (line[0] == '@') {
        return A_TYPE_INSTRUCTION;
    }
    return C_TYPE_INSTRUCTION;
}

void parse(char *line, hack_addr *line_number) {
    if (!line || !line_number) return;

    char label[MAX_LABEL_LENGTH];
    instr_type type = parse_line(line);

    if (is_label(line)) {
        if (extract_label(line, label)) {
            symtable_insert(label, *line_number);
        }
    } else if (type != INVALID_INSTRUCTION) {
        (*line_number)++;
    }
}