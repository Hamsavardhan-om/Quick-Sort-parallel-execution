#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 50000000

int arr[MAX_SIZE];

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high- 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		#pragma omp task firstprivate(arr,low,pi)
		{
			quickSort(arr,low, pi - 1);
		}

		{
			quickSort(arr, pi + 1, high);
		}
	}
}

void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
	printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	double start_time, run_time;
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
    fscanf(fptr,"%d", &arr[i]);
    fclose(fptr);

    omp_set_num_threads(8);
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        #pragma omp single nowait
        quickSort(arr, 0, 100000 - 1);
    }

    run_time = omp_get_wtime() - start_time;
    printf("\nTime taken to sort: %f seconds\n",run_time);
    return 0;
}