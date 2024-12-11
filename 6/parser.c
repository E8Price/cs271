#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"


void add_predefined_symbols(){
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.value);
	}
}

void parse_C_instruction(char *line, c_instruction *instr){
	char *temp;
	char *jump;
	char *comp;
	char *dest;
	temp = strtok(line, ";");
	jump = strtok(NULL, ";");
	if (jump != NULL){	
		dest = strtok(line, "=");
		comp = strtok(NULL, "=");
	}else{
		dest = strtok(line, "=");
		comp = strtok(NULL, "=");
	}
	int a = 0;
	if (comp == NULL){
		instr->comp = str_to_compid(dest, &a);
		instr->dest = str_to_destid("0");
		instr->jump = str_to_jumpid(jump);
	}else{
		instr->comp = str_to_compid(comp, &a);
		instr->dest = str_to_destid(dest);
		instr->jump = str_to_jumpid(jump);
	}
	instr->a = a;
}

bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s = (char*)malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);
	if (s==s_end){
		instr->instrs.label = (char*)malloc(strlen(line));
		strcpy(instr ->instrs.label, s);
		instr->is_addr = false;

	}else if (*s_end != 0){
		return false;
	}else{
		instr->instrs.address = result;
		instr->is_addr = true;
	}
	return true;
}

char* extract_label(const char* line) {
    char* new_line = malloc(strlen(line) + 1);
    int i = 0;
	int j = 0;
    for(i = 0; line[i] != '\0'; i++) {
        if(line[i] != '(' && line[i] != ')') {
            new_line[j++] = line[i];
        }
    }
    new_line[j] = '\0';
	
    return new_line;
}


bool is_Atype(const char* line){
	return (line[0] == '@');
}

bool is_label(const char* line){
	return (line[0] == '(');
}

bool is_Ctype(const char* line){
	return (!is_Atype(line) && !is_label(line));
}

char *strip(char *s){	
	char *s_new = (char*)malloc(strlen(s)+1);
	int i = 0;
	for (char *s2 = s; *s2; s2++) { 
		if (*s2 =='/' && *(s2+1)=='/'){
			if (*(s2-1)){
				s_new[i++]='\0';
			}
			break;
		}if (*s2 == '\n' && *(s2-1)){
		}else if (!isspace(*s2)){
			s_new[i++]=*s2;
		}
	}
	s_new[i]='\0';
	strcpy(s,s_new);
    return s;	
}

int parse(FILE * file, instruction *instructions){
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_number = 0;
	unsigned int instr_num = 0;
	instruction instr;
	
	add_predefined_symbols();
	while (fgets(line,sizeof(line),file)){
		line_number++;
		char inst_type;
		if (instr_num>MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS+1);
		}
		strip(line);
		if (line[0] != '\n' && line[0] != '\0' && line[0] != '/'){
			if (is_Atype(line)){
				inst_type = 'A';
				if (!parse_A_instruction(line, &instr.a)){
    				exit_program(EXIT_INVALID_A_INSTR, line_number, line);
 					}
 				instr.type = a_type;
			}else if (is_label(line)){
				inst_type = 'L';
				char* extracted_line = extract_label(line);
				if (!isalpha(line[1])){
					exit_program(EXIT_INVALID_LABEL, line_number,extracted_line);
				}else if (symtable_find(extracted_line)!=NULL){
					exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_number,extracted_line);
				}else{
					symtable_insert(extracted_line, instr_num);
					continue;
					strcpy(line, extracted_line);
					
				}
				
			}else if (is_Ctype(line)){
				inst_type = 'C';
				instr.type = c_type;
				char tmp_line[MAX_LINE_LENGTH];
				strcpy(tmp_line, line);
				parse_C_instruction(tmp_line, &instr.c);
				if (instr.c.dest == -1){
					exit_program(EXIT_INVALID_C_DEST, line_number, line);
				}else if (instr.c.comp == -1){
					exit_program(EXIT_INVALID_C_COMP, line_number, line);
				}else if (instr.c.jump == -1){
					exit_program(EXIT_INVALID_C_JUMP, line_number, line);
				}
			}
			if (instr.type == a_type){
				if (instr.a.is_addr){
				}else{
				}
			}else{
				int newC;
				if (abs(instr.c.comp) < 16){
						newC = instr.c.comp & 0xF;
					} else if (abs(instr.c.comp) < 64) {
						newC = instr.c.comp & 0x3F;
					} 

			}
				
		instructions[instr_num++] = instr;
		}
	}
	
	return instr_num;
}

void assemble(const char *filename, instruction* instructions, int num_instructions){
	char *hack_filename = (char*)malloc(strlen(filename)+5);
	strcpy(hack_filename, filename);
	strcat(hack_filename, ".hack");
	FILE *hack_file = fopen(hack_filename, "w");
	int newVar = 16;
	for (int i = 0; i < num_instructions; i++){
		instruction instr = instructions[i];
		opcode op;
		if (instr.type == a_type){
			if (!instr.a.is_addr){
				if (symtable_find(instr.a.instrs.label)){
					op=symtable_get_address(instr.a.instrs.label);

	
				}else{
					op = newVar;
					symtable_insert(instr.a.instrs.label, newVar++);
					free(instr.a.instrs.label);
				}
			}else if (instr.a.is_addr){
				op=instr.a.instrs.address;
			}
		} else if (instr.type == c_type){
			op = instruction_to_opcode(instr.c);
		}
		fprintf(hack_file, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(op));
	}
	fclose(hack_file);
}

opcode instruction_to_opcode(c_instruction instr){
	opcode op = 0;
	op |= (7 << 13);
	op |= (instr.a << 12);
	op |= (instr.comp << 6);
	op |= (instr.dest << 3);
	op |= (instr.jump);
	return op;
}