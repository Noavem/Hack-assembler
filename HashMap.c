#include <stdint.h>
#include <stdlib.h>
#include "PearsonHashing.h"
#include "HashMap.h"

hash_map* create_map(size_t size) {
    hash_map* result = malloc(sizeof(hash_map));
    if (result == NULL) {
        return NULL;
    }

    result->size = size;
    result->entries = malloc(size * sizeof(map_entry));
    if (result->entries== NULL) {
        free(result->entries);
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        result->entries[i].key = NULL;
        result->entries[i].value = 0;
        result->entries[i].is_dynamic = 0;
    }
    return result;
}

void insert_general(hash_map *map, char *key, uint16_t value, uint8_t is_key_dynamic) {
    uint16_t hash = pearson_hashing(key);
    uint8_t can_insert = 0;
    int added = 0;

    while (can_insert == 0) {
        if (map->entries[(hash+added)%(map->size)].key != NULL) {
            if (strcmp(map->entries[(hash+added)%(map->size)].key, key) == 0) {
                can_insert = 1;
            } else {
                added += 1;
            }
            if (added > map->size) return;
        } else {
            can_insert = 1;
        }
    }
    map->entries[(hash+added)%(map->size)].key = key;
    map->entries[(hash+added)%(map->size)].value = value;
    map->entries[(hash+added)%(map->size)].is_dynamic = is_key_dynamic;
    map->element_amount += 1;

    if (map->element_amount > (0.7 * map->size)) {
        map_entry *new_entries = malloc(2 * map->size * sizeof(map_entry));
        map_entry *old_entries = map->entries;
        map->size = 2 * map->size;
        map->element_amount = 0;
        map->entries = new_entries;
        for (size_t i = 0; i < (map->size)/2; i++) {
            if (old_entries[i].key != NULL) {
                if (old_entries[i].is_dynamic == 1) {
                    insert_dynamic(map, old_entries[i].key, old_entries[i].value);
                } else {
                    insert(map, old_entries[i].key, old_entries[i].value);
                }
            }
        }
        free(old_entries);
    }
}

void insert_dynamic(hash_map *map, char *key, uint16_t value) {
    insert_general(map, key, value, 1);
}

/* TODO: add dynamic resizing */
void insert(hash_map *map, char *key, uint16_t value) {
    insert_general(map, key, value, 0);
}

uint16_t search(hash_map *map, char *key) {
    uint8_t found = 0;
    uint16_t value = 0;
    uint16_t hash = pearson_hashing(key);
    int added = 0;
    while (found == 0) {
        char* entry_key = map->entries[(hash+added) % map->size].key;
        if ((entry_key != NULL) && (strcmp(entry_key, key) == 0)) {
            value = map->entries[(hash+added) % map->size].value;
            found = 1;
        } else {
            added += 1;
        }
        if (added > map->size) return 0;
    }
    return value;
}

uint8_t contains(hash_map *map, char *key) {
    uint16_t hash = pearson_hashing(key);
    int added = 0;
    while (1) {
        if (map->entries[(hash+added) % map->size].key == NULL) {
            return 0;
        }
        if (strcmp(map->entries[(hash+added) % map->size].key, key) == 0) {
            return 1;
        }
        added += 1;
    }
}

void free_hash_map(hash_map *map) {
    if (map == NULL) {
        return;
    }

    for (size_t i = 0; i < map->size; i++) {
        if (map->entries[i].key != NULL && map->entries[i].is_dynamic == 1) {
            free(map->entries[i].key);
            map->entries[i].key = NULL;
        }
    }

    free(map->entries);
    map->entries = NULL;
    free(map);
}