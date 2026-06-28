#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* selection_sort(int arr[], int n) {
    for (int i = 0; i < n; i++){
        int min = i;

        for (int j = i; j < n; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }

        if (min != i) {
            swap(&arr[i], &arr[min]);
        }
    }

    return arr;
}


int main() 
{
    int size = 7;
    int arr[7] = {5, 9, 8, 4, 2, 7, 3};

    printf("Unsorted array:\n");
    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]);

    printf("\n");

    printf("Sorted array:\n");
    selection_sort(arr, size);

    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}
