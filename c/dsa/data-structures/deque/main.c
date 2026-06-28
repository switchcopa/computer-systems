#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "deque.h"

int main(void) {
        size_t size = 100;
        deque* dq = create_deque(size);  
        
        if (!dq) return 1;

        push_front(dq, 8);
        push_back(dq, 5);
        push_back(dq, 1);
        
        print_deque(dq);

        printf("back index: %d, front index: %d\n", dq->rear, dq->front);
        uint8_t item_1 = pop_back(dq); 
        uint8_t item_2 = pop_front(dq);
        printf("popped items: %u from back, %u from front\n", item_1, item_2); 
        print_deque(dq);

        uint8_t item_3 = pop_back(dq); 
        print_deque(dq);
        if (is_empty(dq)) printf("deque is empty now\n");

        free(dq->buffer);
        free(dq);
        return 0;
}
