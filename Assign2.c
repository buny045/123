#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void quicksort(int a[], int first, int last);
void merge(int a[], int low, int mid, int high);
void divide(int a[], int low, int high);

int main() {
    int a[20], n, i;
    pid_t pid;

    printf("Enter size of the array: ");
    scanf("%d", &n);

    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid = fork();

    switch (pid) {
        case 0: 
            printf("I am child, my ID: %d\n", getpid());
            printf("I am child, my Parent ID: %d\n", getppid());
            quicksort(a, 0, n - 1);
            _exit(0); 
            break;

        case -1: 
            printf("The child process has not been created\n");
            return 1;

        default: 
            wait(NULL);
            printf("I am in default, process ID: %d\n", getpid());
            divide(a, 0, n - 1);
            printf("\nSorted elements:\n");
            for (i = 0; i < n; i++)
                printf("\t%d", a[i]);
            printf("\n");
            break;
    }

    return 0;
}

void divide(int a[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        divide(a, low, mid);
        divide(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void merge(int a[], int low, int mid, int high) {
    int i, j, k;
    int m = mid - low + 1;
    int n = high - mid;
    

    int *first_half = (int *)malloc(m * sizeof(int));
    int *second_half = (int *)malloc(n * sizeof(int));
    
    if (first_half == NULL || second_half == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }


    for (i = 0; i < m; i++)
        first_half[i] = a[low + i];
    for (i = 0; i < n; i++)
        second_half[i] = a[mid + 1 + i];

    i = j = 0;
    k = low;
    while (i < m && j < n) {
        if (first_half[i] <= second_half[j])
            a[k++] = first_half[i++];
        else
            a[k++] = second_half[j++];
    }


    while (i < m)
        a[k++] = first_half[i++];

    while (j < n)
        a[k++] = second_half[j++];


    free(first_half);
    free(second_half);
}

void quicksort(int a[], int first, int last) {
    int pivot, j, temp, i;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (a[i] <= a[pivot] && i < last)
                i++;
            while (a[j] > a[pivot])
                j--;
            if (i < j) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        temp = a[pivot];
        a[pivot] = a[j];
        a[j] = temp;
        quicksort(a, first, j - 1);
        quicksort(a, j + 1, last);
    }
}

