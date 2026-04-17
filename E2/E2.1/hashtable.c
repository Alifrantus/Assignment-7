#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) table->buckets[i] = NULL;
    return table;
}

unsigned int hash(char *str) {
    unsigned int h = 0;
    for (int i = 0; str[i] != '\0'; i++) h = h * 31 + str[i];
    return h % TABLE_SIZE;
}

void insert(HashTable* table, char *name, char *phone) {
    unsigned int index = hash(name);
    Node* newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

void search(HashTable* table, char *name) {
    unsigned int index = hash(name);
    Node* temp = table->buckets[index];
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            printf("Found: %s - %s\n", name, temp->phone);
            return;
        }
        temp = temp->next;
    }
    printf("Contact %s not found.\n", name);
}

void delete_contact(HashTable* table, char *name) {
    unsigned int index = hash(name);
    Node *temp = table->buckets[index], *prev = NULL;
    while (temp && strcmp(temp->name, name) != 0) {
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