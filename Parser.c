#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "SymbolTable.h"
#include "Parser.h"

void parse_label(char *stripped_line, hash_map *symbol_map, int line_number) {
    if (stripped_line[0] == '(') {
        char *symbol = stripped_line + 1;

        /* Find real length of symbol */
        int i = 0;
        while (symbol[i] != ')' && symbol[i] != '\n' && symbol[i] != ' ') {
            i++;
        }

        /* Copy symbol into new memory locations */
        char *symbol_string = malloc((i+1)*sizeof(char));
        for (int n = 0; n < i; n++) {
            symbol_string[n] = symbol[n];
        }
        symbol_string[i] = '\0';
        insert_dynamic(symbol_map, symbol_string, line_number-1);
    }
}

uint16_t parse_a_instruction(hash_map *symbol_map, int *symbol_index, char *symbol) {
    if (!isdigit((unsigned char)symbol[0])) {
        char *symbol_string = parse_a_symbol(symbol);
        if (!contains(symbol_map, symbol_string)) {
            insert_dynamic(symbol_map, symbol_string, *symbol_index);
            (*symbol_index)++;
        }
        return handle_a_instruction_symbolic(symbol_map, symbol_string);
    } else {
        char *symbol_string = parse_a_symbol(symbol);
        int number = atoi(symbol_string);
        return handle_a_instruction_numeric(symbol_map, number);
    }
}

char* parse_a_symbol(char *symbol) {
    int i = 0;
    /* Find real length of symbol */
    while (symbol[i] != '\r' && symbol[i] != '\n' && symbol[i] != ' ') {
        i++;
    }
    /* Copy symbol into new memory locations */
    char *symbol_string = malloc((i+1)*sizeof(char));
    for (int n = 0; n < i; n++) {
        symbol_string[n] = symbol[n];
    }
    symbol_string[i] = '\0';
    return symbol_string;
}

uint16_t parse_c_instruction(char *command, hash_map *comp_map, hash_map *dest_map, hash_map *jump_map) {
    char *comp = NULL;
    char *dest = NULL;
    char *jump = NULL;
    int i = 0;

    while (command[i] != '=' && command[i] != ';' && command[i] != '\r' && command[i] != '\n') {
        i++;
    }
    if (i > 0) {
        dest = malloc((i+1)*sizeof(char));
        for (int n = 0; n < i; n++) {
            dest[n] = command[n];
        }
        dest[i] = '\0';
    }
    if (command[i] == '=') {
        i++;
        }
    int i_temp = i;
    while (command[i] != ';' && command[i] != '\r' && command[i] != '\n') {
        i++;
    }
    if (i > i_temp) {
        comp = malloc((i-i_temp+1)*sizeof(char));
        for (int n = i_temp; n < i; n++) {
            comp[n-i_temp] = command[n];
        }
        comp[i] = '\0';
    }
    if (command[i] == ';') {
        i++;
    }
    i_temp = i;
    while (command[i] != '\r' && command[i] != '\n' && command[i] != ' ') {
        i++;
    }
    if (i > i_temp) {
        jump = malloc((i-i_temp+1)*sizeof(char));
        for (int n = i_temp; n < i; n++) {
            jump[n-i_temp] = command[n];
        }
        jump[i] = '\0';
    }
    if (comp == NULL) {
        return handle_c_instruction(comp_map, dest_map, jump_map, dest, comp, jump);
    } else {
        return handle_c_instruction(comp_map, dest_map, jump_map, comp, dest, jump);
    }
}

uint16_t handle_a_instruction_numeric(hash_map *symbols, int address) {
    uint16_t instruction = (uint16_t)32767 & (uint16_t)address;
    return instruction;
}

uint16_t handle_a_instruction_symbolic(hash_map *symbols, char *symbol) {
    uint16_t instruction = (uint16_t)32767 & (uint16_t)search(symbols, symbol);
    return instruction;
}

uint16_t handle_c_instruction(hash_map *comp_map, hash_map *dest_map, hash_map *jump_map, char *comp, char *dest, char *jump) {
    uint16_t instruction = 57344;
    if (comp != NULL) instruction = instruction | (search(comp_map, comp) << 6);
    if (dest != NULL) instruction = instruction | (search(dest_map, dest) << 3);
    if (jump != NULL) instruction = instruction | search(jump_map, jump);
    return instruction;
}