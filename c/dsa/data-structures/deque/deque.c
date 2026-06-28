#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "deque.h"

deque* create_deque(size_t size) {
    deque* dq = malloc(sizeof(deque));
    if (!dq) return NULL;

    dq->buffer = malloc(sizeof(uint8_t) * size);
    if (!dq->buffer) {
        free(dq);
        return NULL;
    }

    dq->capacity = size;
    dq->size = 0;
    dq->front = -1;
    dq->rear = -1;

    return dq;
}

bool is_empty(deque* dq) {
    if (!dq) return true;
    return dq->size == 0;
}

bool is_full(deque* dq) {
    if (!dq) return false;
    return dq->size == dq->capacity;
}

void push_front(deque* dq, uint8_t data) {
    if (!dq || is_full(dq)) return;

    if (is_empty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    }

    dq->buffer[dq->front] = data;
    dq->size++;
}

void push_back(deque* dq, uint8_t data) {
    if (!dq || is_full(dq)) return;

    if (is_empty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % dq->capacity;
    }

    dq->buffer[dq->rear] = data;
    dq->size++;
}

uint8_t pop_front(deque* dq) {
    if (!dq || is_empty(dq)) return 0;

    uint8_t data = dq->buffer[dq->front];

    if (dq->size == 1) { 
        dq->front = dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % dq->capacity;
    }

    dq->size--;
    return data;
}

uint8_t pop_back(deque* dq) {
    if (!dq || is_empty(dq)) return 0;

    uint8_t data = dq->buffer[dq->rear];

    if (dq->size == 1) {  
        dq->front = dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;
    }

    dq->size--;
    return data;
}

void print_deque(deque* dq) {
    if (!dq) {
        printf("deque is NULL\n");
        return;
    }

    if (is_empty(dq)) {
        printf("deque is empty\n");
        return;
    }

    printf("[ ");
    for (int i = dq->front, count = 0; count < dq->size; i = (i + 1) % dq->capacity) {
        printf("%u ", dq->buffer[i]);
        count++;
    }
    printf("]\n");
}

