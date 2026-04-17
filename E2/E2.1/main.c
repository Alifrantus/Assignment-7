#include <stdio.h>
#include "hashtable.h"

int main() {
    HashTable* ht = create_table();
    
    printf("Inserting: (1, 100), (11, 200), (2, 300)\n");
    insert(ht, 1, 100);
    insert(ht, 11, 200);
    insert(ht, 2, 300);

    printf("Search Key 11: %d\n", search(ht, 11));
    
    printf("Deleting Key 11...\n");
    delete_node(ht, 11);
    printf("Search Key 11 after deletion: %d\n", search(ht, 11));

    free_table(ht);
    return 0;
}