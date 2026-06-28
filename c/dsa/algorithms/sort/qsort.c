#include <stdio.h> 

int partition(int [], int, int);
void qsort(int [], int, int);
void swap(int *, int *);

int main(void) {
	int v[] = {19, 17, 15, 12, 16, 18, 4, 11, 13};
        int size = sizeof(v) / sizeof(int);
        printf("size: %d\n", size);

	qsort(v, 0, size - 1); 
        for (int i = 0; i < size; i++)
                printf("%d ", v[i]);

        printf("\n");
	return 0;
}

int partition(int v[], int low, int high) {
        int i = low - 1;
        int pivot = v[high];
        
        for (int j = low; j <= high - 1; j++) 
                if (pivot < v[j]) {
                        i++;
                        swap(&v[i], &v[j]);
                }

        swap(&v[high], &v[i]);
        return i + 1;
}

void qsort(int v[], int low, int high) {
        if (low < high) {
                int pi = partition(v, low, high);

                qsort(v, pi + 1, high);
                qsort(v, low, pi - 1);
        }
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
