#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char *key;
    uint16_t value;
    uint8_t is_dynamic;
} map_entry;

typedef struct {
    map_entry *entries;
    size_t size;
    size_t element_amount;
} hash_map;

hash_map *create_map(size_t size);

void insert_dynamic(hash_map *map, char *key, uint16_t value);

void insert(hash_map *map, char *key, uint16_t value);

uint16_t search(hash_map *map, char *key);

uint8_t contains(hash_map *map, char *key);

void free_hash_map(hash_map *map);

#endif