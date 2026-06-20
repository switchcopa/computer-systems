#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define INIT_REGISTRY_SIZE 100

typedef struct
{
    void **registry;
    size_t capacity;
    size_t size;
} AllocRegistry;

AllocRegistry   init_registry(void);
void*           hmalloc(AllocRegistry *reg, size_t size);
void            hfree(AllocRegistry *reg);
void            print_registry(AllocRegistry *reg);

int
main(void)
{
    AllocRegistry reg = init_registry();
    for (int i = 0; i < INIT_REGISTRY_SIZE; i++)
    {
        void *p = hmalloc(&reg, sizeof(char) * 8);
    }
    print_registry(&reg);

    int *arr3 = hmalloc(&reg, sizeof(int) * 5);
    print_registry(&reg);
    
    hfree(&reg);
    print_registry(&reg);

    return 0;
}

AllocRegistry
init_registry(void)
{
    AllocRegistry reg;
    reg.registry = malloc(sizeof(void *) * INIT_REGISTRY_SIZE);
    if (!reg.registry)
    {
        reg.capacity = 0;
        reg.size = 0;
        return reg;
    }
    
    reg.capacity = INIT_REGISTRY_SIZE;
    reg.size = 0;

    for (size_t i = 0; i < reg.capacity; i++)
        reg.registry[i] = NULL;
    return reg;
}

void *
hmalloc(AllocRegistry *reg, size_t size)
{
    void *p = malloc(size);
    if (!p) return NULL;

    if (reg->size >= reg->capacity)
    {
        void *nreg = realloc(reg->registry, 2 * reg->capacity * sizeof(void *));
        if (!nreg)
        {
            free(p);
            return NULL;
        }
        
        reg->registry = nreg;
        reg->capacity *= 2;
     }

    reg->registry[reg->size++] = p;
    return p;
}


void
hfree(AllocRegistry *reg)
{
    for (size_t i = 0; i < reg->size; i++)
        free(reg->registry[i]);
    reg->size = 0;
}

void
print_registry(AllocRegistry *reg)
{
    if (reg->size == 0)
    {
        printf("Registry empty.\n");
        return;
    }

    printf("Size of registry: %zu\n", reg->size);
    printf("Capacity of registry: %zu\n", reg->capacity);
    printf("Memory layout:\n\n");
    for (size_t i = 0; i < reg->size; i++)
        printf("%p\n", reg->registry[i]);
    printf("\n");
}
