#include "HashMap.h"

hash_map *create_symbol_map() {
    hash_map *map = create_map(32);
    insert(map, "SP", 0b000);
    insert(map, "LCL", 0b001);
    insert(map, "ARG", 0b010);
    insert(map, "THIS", 0b011);
    insert(map, "THAT", 0b100);
    insert(map, "LOOP", 0b100);
    insert(map, "R0", 0b000);
    insert(map, "R1", 0b001);
    insert(map, "R2", 0b010);
    insert(map, "R3", 0b011);
    insert(map, "R4", 0b100);
    insert(map, "R5", 0b101);
    insert(map, "R6", 0b110);
    insert(map, "R7", 0b111);
    insert(map, "R8", 0b1000);
    insert(map, "R9", 0b1001);
    insert(map, "R10", 0b1010);
    insert(map, "R11", 0b1011);
    insert(map, "R12", 0b1100);
    insert(map, "R13", 0b1101);
    insert(map, "R14", 0b1110);
    insert(map, "R15", 0b1111);
    insert(map, "STOP", 0b10010);
    insert(map, "i", 0b10000);
    insert(map, "sum", 0b10001);
    insert(map, "SCREEN", 0b100000000000000);
    insert(map, "KBD", 0b110000000000000);
    return map;
}