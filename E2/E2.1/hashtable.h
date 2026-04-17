#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// Library Interface
HashTable* create_table();
int hash_function(int key);
void insert(HashTable* table, int key, int value);
int search(HashTable* table, int key);
void delete_node(HashTable* table, int key);
void free_table(HashTable* table);
void print_table(HashTable* table);

#endif