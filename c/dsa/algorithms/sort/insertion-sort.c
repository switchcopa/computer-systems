#include <stdio.h>

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int n) 
{
    for (int i = 0; i < n; i++) {
        int j = i - 1;

        while (j>=0 && arr[j] > arr[j+1]) {
            swap(&arr[j], &arr[j+1]);
            j--;
        }
    }
}

int main() 
{   
    int size = 7;
    int arr[7] = {9, 2, 8, 3, 7, 1, 4};

    printf("Unordered array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    insertion_sort(arr, 7);
    
    printf("Orderd array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
