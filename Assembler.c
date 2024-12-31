#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HashMap.h"
#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"

///////////////////////
// Name:        Assembler.c
// Author:      Noavem
// Description: Assembler for the Hack assembly language.
///////////////////////

char *strip_leading_whitespace(char *line) {
    while (isspace((unsigned char)*line)) {
        line++;
    }
    return line;
}

void write_binary_to_file(uint16_t *instructions, int instruction_index, FILE *output, int line_amount) {
    int binaryRep[16] = { 0 };
    int l = 0;
    int num = instructions[instruction_index];
    while (num > 0) {
        binaryRep[l] = num % 2;
        num = num / 2;
        l++;
    }
    for (int j = 15; j >= 0; j--) {
        fprintf(output, "%d", binaryRep[j]);
    }
    if (instruction_index + 1 < line_amount) fprintf(output, "\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.asm>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Something went wrong while writing to the file!");
        return EXIT_FAILURE;
    }

    FILE* output = fopen("output.hack", "w");
    if (!output) {
        perror("Something went wrong while writing to the file!");
        return EXIT_FAILURE;
    }

    /* First pass to parse label symbols */ 
    char line[256];
    int symbol_index = 16;
    hash_map *symbol_map = create_symbol_map();
    hash_map *comp_map = create_comp_map();
    hash_map *dest_map = create_dest_map();
    hash_map *jump_map = create_jump_map();

    int line_number = 1;
    while (fgets(line, sizeof(line), file)) {
        char *stripped_line = strip_leading_whitespace(line);
        parse_label(stripped_line, symbol_map, line_number);
        if (isdigit(stripped_line[0]) || isalpha(stripped_line[0]) || (stripped_line[0] == '@')) line_number++;
    }
    int line_amount = line_number - 1;

    /* Second pass to parse the actual instructions */
    rewind(file);
    int instruction_index = 0;
    uint16_t instructions[line_amount];
    while (fgets(line, sizeof(line), file)) {
        char *stripped_line = strip_leading_whitespace(line);
        
        if (stripped_line[0] == '@') {
            char *symbol = stripped_line + 1;
            instructions[instruction_index] = parse_a_instruction(symbol_map, &symbol_index, symbol);
        } else if (isdigit(stripped_line[0]) || isalpha(stripped_line[0])) {
            char *command = stripped_line;
            instructions[instruction_index] = parse_c_instruction(command, comp_map, dest_map, jump_map);
        } else {
            continue;
        }
        write_binary_to_file(instructions, instruction_index, output, line_amount);
        instruction_index++;
    }
    fclose(output);
    fclose(file);
    free_hash_map(comp_map);
    free_hash_map(dest_map);
    free_hash_map(jump_map);
    free_hash_map(symbol_map);
}