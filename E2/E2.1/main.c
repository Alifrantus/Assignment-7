#include "hashtable.h"
#include <stdio.h>

int main() {
    HashTable* ht = create_table();

    insert(ht, "An", "0901");
    insert(ht, "Binh", "0902");

    search(ht, "An");
    delete_contact(ht, "An");
    search(ht, "An");

    free_table(ht);
    return 0;
}