#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"

#define MAX_LINE_LENGTH  200


void add_predefined_symbols(){
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        predefined_symbol ps = predefined_symbols[i];
        symtable_insert(ps.name, ps.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = "";
    s = malloc(sizeof(line));
    strcpy(s, line+1);
    
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if(s == s_end){
        instr->operand.label = malloc(strlen(line));
        strcpy(instr->operand.label, s);
        instr->is_addr = false;
    } else if (*s_end != 0){
        return false;
    } else {
        instr->operand.address = result;
        instr->is_addr = true;
    }
    return true;
}

char *extract_label(const char *line, char* label){
    int i = 0;
    for(const char *s = line;  *s++;){
        if((*s == '(') || (*s == ')')){
            continue;
        } else {
            label[i++] = *s;
        }
    }
    label[i] = '\0';
    return label;

}
    


bool is_Atype(const char *line){
    if(line[0] == '@'){
        return  1;
    }else{
        return  0;
    }
}


bool is_label(const char *line){
    if((line[0] == '(') && (line[strlen(line)-1]) == ')'){
        return 1;
    } else {
        return 0;
    }
}


bool is_Ctype(const char *line){
    if((line[0] == 'M') || (line[0] == 'D') || (line[0] == '0') || (line[0] == 'A')){
        return 1;
    } else {
        return 0;
    }
}



char *strip(char *s){	

    char s_new[strlen(s) + 1];
    int i = 0;
    
    for (char *s2 = s; *s2; s2++) {
       
        if((*s2 == '/') && (*(s2+1) == '/')){
            break;
        } else if(!isspace(*s2)) {
            s_new[i++] = *s2;
        }
        
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    
    return s;	
}


void parse(FILE * file){
    instruction instr;

	
    char line[MAX_LINE_LENGTH]={0};
    char label[MAX_LABEL_LENGTH] = {0};
    
    unsigned int counter = 0;
   
    unsigned int line_num  = *line;
    unsigned int instr_num = counter;
    
    add_predefined_symbols();
    
    while(fgets(line, sizeof(line), file)){
        
        line_num++;
        
        if(instr_num  > MAX_INSTRUCTIONS){
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
            
            
        strip(line);
        
        if(*line == '\0'){
            continue;
        }
    
      
        
        
        if(is_Atype(line) == 1){

            if (!parse_A_instruction(line, &instr.instr.a)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
             }
             instr.sometype = A_type;
        }
        
        if(is_label(line) == 1){
            
            
            
            strcpy(line, extract_label(line, label));
            
            if (!isalpha(*label))
                exit_program(EXIT_INVALID_LABEL, line_num, line);
            
            
            if(symtable_find(label) != NULL)
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
            
            
            symtable_insert(label, instr_num);
            continue;
        }
        
        if(is_Ctype(line) == 1){
           
        }

         instr_num++;
    }
}