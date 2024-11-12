/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $YOUR_NAME$
 * [TERM] FALL $YEAR$
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s) {    
    char s_new[MAX_LINE_LENGTH + 1];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2 + 1) == '/') {
            break;
        }
        else if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }
    
    s_new[i] = '\0';
    strcpy(s, s_new);
    
    return s;    
}

// Determine if the line is an A-type instruction (starts with @)
bool is_Atype(const char *line) {
    return line[0] == '@';
}

// Determine if the line is a label (starts with '(' and ends with ')')
bool is_label(const char *line) {
    int len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

// Determine if the line is a C-type instruction (anything not A-type or label)
bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

// Updated parse function to label each line as A, L, or C type
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH];
    char inst_type;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        strip(line);
        if (!*line) {
            continue;
        }
        
        // Determine instruction type
        if (is_Atype(line)) {
            inst_type = 'A';
        } else if (is_label(line)) {
            inst_type = 'L';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
        }

        // Print the instruction type followed by the line
        printf("%c  %s\n", inst_type, line);
    }
}
