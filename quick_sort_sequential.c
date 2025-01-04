#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define MAX_SIZE 50000001

void swap(int* p1, int* p2) 
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int *arr, int low, int high) 
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) 
    {
        if (arr[j] < pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int *arr, int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() 
{
    FILE *fptr;
    fptr = fopen("numbers.txt","r");
    int* arr = (int*) malloc(MAX_SIZE * sizeof(int));
    if (arr == NULL) 
    {
        printf("Memory allocation failed\n");
        fclose(fptr); 
        return 1; 
    }

    for (int i = 0; i < 100000; i++) 
    {
        fscanf(fptr,"%d", &arr[i]);
    }
    fclose(fptr);
    clock_t start, end;  
    double cpu_time_used;

    start = clock();

    quickSort(arr, 0, 100000 - 1);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort: %f seconds\n", cpu_time_used);

    free(arr);
    return 0;
}
