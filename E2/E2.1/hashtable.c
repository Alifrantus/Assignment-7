#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) table->buckets[i] = NULL;
    return table;
}

int hash_function(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable* table, int key, int value) {
    int index = hash_function(key);
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

int search(HashTable* table, int key) {
    int index = hash_function(key);
    Node* temp = table->buckets[index];
    while (temp) {
        if (temp->key == key) return temp->value;
        temp = temp->next;
    }
    return -1; // Not found
}

void delete_node(HashTable* table, int key) {
    int index = hash_function(key);
    Node *temp = table->buckets[index], *prev = NULL;
    while (temp && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev) table->buckets[index] = temp->next;
    else prev->next = temp->next;
    free(temp);
}

void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = table->buckets[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(table);
}