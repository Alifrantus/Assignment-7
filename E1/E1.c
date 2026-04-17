#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// 1. Data Structure Definitions
typedef struct Node {
    char name[50];
    char phone[15];
    struct Node* next;
} Node;

Node* buckets[TABLE_SIZE];

// 2. Polynomial Hash Function
unsigned int hash(char *str) {
    unsigned int h = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        h = h * 31 + str[i];
    }
    return h % TABLE_SIZE;
}

// 3. Mandatory Functions
void insert(char *name, char *phone) {
    unsigned int index = hash(name);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    
    // Add to head of the linked list (Chaining)
    newNode->next = buckets[index];
    buckets[index] = newNode;
}

char* search(char *name) {
    unsigned int index = hash(name);
    Node* temp = buckets[index];
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) return temp->phone;
        temp = temp->next;
    }
    return NULL;
}

void delete_contact(char *name) {
    unsigned int index = hash(name);
    Node *temp = buckets[index], *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; // Not found

    if (prev == NULL) buckets[index] = temp->next; // Node is head
    else prev->next = temp->next;

    free(temp);
    printf("Deleted contact: %s\n", name);
}

void print_all() {
    printf("\n--- Current Phonebook ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket [%d]: ", i);
        Node* temp = buckets[i];
        while (temp) {
            printf("(%s: %s) -> ", temp->name, temp->phone);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// 4. Testing Requirement
int main() {
    for (int i = 0; i < TABLE_SIZE; i++) buckets[i] = NULL;

    // Insert 8 contacts
    insert("An", "0901"); insert("Binh", "0902");
    insert("Chi", "0903"); insert("Dung", "0904");
    insert("Giang", "0905"); insert("Hoa", "0906");
    insert("Linh", "0907"); insert("Nam", "0908");

    print_all();

    // Search 3 names
    char* targets[] = {"An", "Linh", "Xuan"};
    for (int i = 0; i < 3; i++) {
        char* result = search(targets[i]);
        if (result) printf("Found %s: %s\n", targets[i], result);
        else printf("%s not found in phonebook.\n", targets[i]);
    }

    // Delete 2 contacts
    delete_contact("An");
    delete_contact("Dung");

    print_all();

    return 0;
}