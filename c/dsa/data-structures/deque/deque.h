#ifndef DEQUE_H 
#define DEQUE_H 

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_DEQUE_SIZE 10

typedef struct {
        uint8_t* buffer;
        size_t capacity;
        size_t size;
        signed int rear;
        signed int front;
} deque;

deque* create_deque(size_t size);
bool is_empty(deque* dq);
bool is_full(deque* dq);
void push_front(deque* dq, uint8_t data);
void push_back(deque* dq, uint8_t data);
uint8_t pop_front(deque* dq);
uint8_t pop_back(deque* dq);
void print_deque(deque* dq);

#endif 
