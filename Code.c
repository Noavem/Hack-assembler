#include "HashMap.h"

hash_map *create_jump_map() {
    hash_map *map = create_map(16);
    insert(map, "NULL", 0b000);
    insert(map, "JGT", 0b001);
    insert(map, "JEQ", 0b010);
    insert(map, "JGE", 0b011);
    insert(map, "JLT", 0b100);
    insert(map, "JNE", 0b101);
    insert(map, "JLE", 0b110);
    insert(map, "JMP", 0b111);
    return map;
}

hash_map *create_comp_map() {
    hash_map *map = create_map(64);
    insert(map, "0", 0b0101010);
    insert(map, "1", 0b0111111);
    insert(map, "-1", 0b0111010);
    insert(map, "D", 0b0001100);
    insert(map, "A", 0b0110000);
    insert(map, "!D", 0b0001101);
    insert(map, "!A", 0b0110001);
    insert(map, "-D", 0b0001111);
    insert(map, "-A", 0b0110011);
    insert(map, "D+1", 0b0011111);
    insert(map, "A+1", 0b0110111);
    insert(map, "D+A", 0b0000010);
    insert(map, "D-A", 0b0010011);
    insert(map, "A-D", 0b0000111);
    insert(map, "D&A", 0b0000000);
    insert(map, "D|A", 0b0010101);
    insert(map, "M", 0b1110000);
    insert(map, "!M", 0b1110001);
    insert(map, "-M", 0b1110011);
    insert(map, "M+1", 0b1110111);
    insert(map, "M-1", 0b1110010);
    insert(map, "D+M", 0b1000010);
    insert(map, "D-M", 0b1010011);
    insert(map, "M-D", 0b1000111);
    insert(map, "D&M", 0b1000000);
    insert(map, "D|M", 0b1010101);
    insert(map, "D-1", 0b0001110);
    insert(map, "A-1", 0b0110010);
    return map;
}

hash_map *create_dest_map() {
    hash_map *map = create_map(16);
    insert(map, "NULL", 0b000);
    insert(map, "M", 0b001);
    insert(map, "D", 0b010);
    insert(map, "MD", 0b011);
    insert(map, "A", 0b100);
    insert(map, "AM", 0b101);
    insert(map, "AD", 0b110);
    insert(map, "AMD", 0b111);
    return map;
}