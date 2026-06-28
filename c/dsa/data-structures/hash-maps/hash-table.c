#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node;
struct HashTable;

struct Node {
    struct Node* next;
    char* key;
    int value;
};

struct HashTable {
    struct Node** buckets;
    int size;
    int numOfElements;
    int collisions;
};

struct HashTable* rehash(struct HashTable* table);

void freeHashTable(struct HashTable* table);

unsigned int hash(char* key, int size);

char* stdup(char* s);

struct HashTable* initHashTable(int size);

float loadFactor(struct HashTable* table);

struct Node* createNode(char* key, int value);

struct HashTable* initHashTable(int size) {
    struct HashTable* table = malloc(sizeof(struct HashTable));
    if (!table) return NULL;

    table->buckets = malloc(sizeof(struct Node*) * size);
    if (!table->buckets) return NULL;

    for (int i = 0; i < size; i++) 
    {
        table->buckets[i] = NULL;
    }
    table->size = size;
    table->numOfElements = 0;
    table->collisions = 0;
    return table;
}

struct Node* createNode(char* key, int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->key = key;
    node->value = value;
    return node;
}

float loadFactor(struct HashTable* table) {
    return (float) table->numOfElements / table->size;
}

char* stdup(char* s) {
    char *p;
    p = malloc(strlen(s) + 1);
    if (!p) return NULL;
    strcpy(p, s);
    return p;
}

unsigned int hash(char* key, int size) {
    unsigned int hashval = 5381;
    int c;

    while ((c = *key++) != '\0')
        hashval = ((hashval << 5) + hashval) + c;

    return hashval % size;
}

void print_table(struct HashTable* table) {
    printf("Hash table: \n");
    for (int i = 0; i < table->size; i++) 
    {
        struct Node* curr = table->buckets[i];
        if (!curr) continue;
        while (curr) {
            printf("(%s, %d) -> ", curr->key, curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}


void insert(struct HashTable** tableRef, char* key, int value) {
    struct HashTable* table = *tableRef;
    int index = hash(key, table->size);

    struct Node* node = createNode(stdup(key), value);
    
    if (table->buckets[index] == NULL) {
        table->buckets[index] = node;
    } else {
        node->next = table->buckets[index];
        table->buckets[index] = node;
        table->collisions++;
    }
    table->numOfElements++;

    if (loadFactor(table) > 0.72)
        *tableRef = rehash(table);
}

bool delete(struct HashTable* table, char* key) {
    int index = hash(key, table->size);
    if (table->buckets[index] == NULL) return false;

    struct Node* curr = table->buckets[index];
    struct Node* prev = NULL;

    while (curr) {
        if (strcmp(key, curr->key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr->key);
            free(curr);
            table->numOfElements--;
            return true;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}

int lookup(struct HashTable* table, char* key) {
    int index = hash(key, table->size);
    if (table->buckets[index] == NULL) return -1;

    struct Node* curr = table->buckets[index];
    while (curr) {
        if (strcmp(key, curr->key) == 0) {
            return curr->value;
        } else {
            curr = curr->next;
        }
    }
    return -1;
}

struct HashTable* rehash(struct HashTable* table) {
    int newSize = table->size * 2;
    struct HashTable* newTable = initHashTable(newSize);

    for (int i = 0; i < table->size; i++) {
        if (table->buckets[i] == NULL) continue;
        struct Node* curr = table->buckets[i];
        while (curr) {
            struct Node* temp = curr;
            insert(&newTable, curr->key, curr->value);
            curr = curr->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
    return newTable;
}

void freeHashTable(struct HashTable* table) 
{
    for (int i = 0; i < table->size; i++) {
        struct Node* curr = table->buckets[i];
        while (curr) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
    return;
}

int main() {
    struct HashTable* table = initHashTable(10);
    insert(&table, "Hello", 5);
    insert(&table, "Neighbor", 1);
    insert(&table, "ni", 3);
    insert(&table, "sheep", 7);
    insert(&table, "television", 10);
    insert(&table, "ryad", 11);
    insert(&table, "terry", 2);
    print_table(table);
    printf("The number of collisions is: %d\n", table->collisions);
    printf("Looking for Hello: %d\n", lookup(table, "Hello"));
    delete(table, "Hello");
    printf("Looking for Hello: %d\n", lookup(table, "Hello"));
    printf("And the load factor is %.2f\n", loadFactor(table));
    table = rehash(table);
    printf("And the load factor is %.2f\n", loadFactor(table));
    print_table(table);
    freeHashTable(table);
    return 0;
}
