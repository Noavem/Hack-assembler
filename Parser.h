#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "SymbolTable.h"

void parse_label(char *strippedLine, hash_map* symbol_map, int lineNumber);

uint16_t parse_a_instruction(hash_map* symbol_map, int* symbol_index, char* symbol);

char *parse_a_symbol(char *symbol);

uint16_t parse_c_instruction(char *command, hash_map *comp_map, hash_map *dest_map, hash_map *jump_map);

uint16_t handle_a_instruction_numeric(hash_map *symbols, int address);

uint16_t handle_a_instruction_symbolic(hash_map *symbols, char *symbol);

uint16_t handle_c_instruction(hash_map *comp_map, hash_map *dest_map, hash_map *jump_map, char *comp, char *dest, char *jump);

#endif