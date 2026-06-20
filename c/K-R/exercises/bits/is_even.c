#include <stdio.h> 
#include <stdbool.h>

bool is_even(int x);

int main(void) {
        int arr[5] = {1,2,5,7,10};
        for (int i = 0; i < 5 ; i++) {
                if (is_even(arr[i])) printf("%d is even\n", arr[i]); 
                else printf("%d is odd\n", arr[i]);
        }

        return 0;
}

bool is_even(int x) {
        return !(x & 1);
}
