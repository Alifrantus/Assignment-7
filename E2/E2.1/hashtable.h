#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 10

typedef struct Node {
    char name[50];
    char phone[15];
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

HashTable* create_table();
unsigned int hash(char *str);
void insert(HashTable* table, char *name, char *phone);
void search(HashTable* table, char *name);
void delete_contact(HashTable* table, char *name);
void free_table(HashTable* table);
void print_table(HashTable* table);

#endif