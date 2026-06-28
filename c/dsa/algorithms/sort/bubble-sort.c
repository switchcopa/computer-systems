#include <stdio.h>

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int n)  {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
}

int main() {
    int arr[7] = {2,7,3,1,9,4,8};
    printf("Unsorted array:\n");
    for (int i = 0; i < 7; i++)
        printf("%d ", arr[i]);

    printf("\n");

    bubble_sort(arr, 7);

    printf("Sorted array:\n");
    for (int i = 0; i < 7; i++)
        printf("%d ", arr[i]);

    printf("\n");
    return 0;
}   
