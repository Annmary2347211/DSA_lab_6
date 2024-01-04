#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee
struct Employee {
    char name[100];
    char department[50];
    int employeeID;
    int joiningYear;
    double salary;
};

// Variables to count comparisons for each sorting technique
int mergeSortComparisons = 0;
int quickSortComparisons = 0;

// Function to print an employee
void printEmployee(struct Employee *employee) {
    printf("Name: %s, Department: %s, Employee ID: %d, Joining Year: %d, Salary: %.2f\n",
           employee->name, employee->department, employee->employeeID, employee->joiningYear, employee->salary);
}

// Function to perform Merge Sort on an array of employees
void merge(struct Employee arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Employee L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        mergeSortComparisons++;  // Increment the comparison count for Merge Sort
        if (L[i].joiningYear <= R[j].joiningYear) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform Merge Sort on an array of employees
void mergeSort(struct Employee arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to partition the array for Quick Sort
int partition(struct Employee arr[], int low, int high) {
    struct Employee pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        quickSortComparisons++;  // Increment the comparison count for Quick Sort
        if (arr[j].joiningYear <= pivot.joiningYear) {
            i++;

            // Swap arr[i] and arr[j]
            struct Employee temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i + 1] and arr[high] (pivot)
    struct Employee temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Function to perform Quick Sort on an array of employees
void quickSort(struct Employee arr[], int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(arr, low, high);

        // Recursive sort the elements before and after the partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to read employees from a file
void readEmployeesFromFile(char *filename, struct Employee arr[], int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *size = 0;
    while (fscanf(file, "%[^,],%[^,],%d,%d,%lf\n", arr[*size].name, arr[*size].department, &arr[*size].employeeID, &arr[*size].joiningYear, &arr[*size].salary) != EOF) {
        (*size)++;
    }

    fclose(file);
}

// Function to write employees to a file
void writeEmployeesToFile(char *filename, struct Employee arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s,%s,%d,%d,%.2f\n", arr[i].name, arr[i].department, arr[i].employeeID, arr[i].joiningYear, arr[i].salary);
    }

    fclose(file);
}

int main() {
    struct Employee employeesMerge[100];
    struct Employee employeesQuick[100];
    int sizeMerge, sizeQuick;

    // Read employees from a file for Merge Sort
    readEmployeesFromFile("employees.txt", employeesMerge, &sizeMerge);

    printf("Original list of employees:\n");
    for (int i = 0; i < sizeMerge; i++) {
        printEmployee(&employeesMerge[i]);
    }

    // Perform Merge Sort
    mergeSort(employeesMerge, 0, sizeMerge - 1);

    printf("\nEmployees after Merge Sort:\n");
    for (int i = 0; i < sizeMerge; i++) {
        printEmployee(&employeesMerge[i]);
    }

    // Write sorted employees to a file for Merge Sort
    writeEmployeesToFile("sorted_employees_merge.txt", employeesMerge, sizeMerge);

    // Read employees from the file again for Quick Sort
    readEmployeesFromFile("employees.txt", employeesQuick, &sizeQuick);

    // Perform Quick Sort
    quickSort(employeesQuick, 0, sizeQuick - 1);

    printf("\nEmployees after Quick Sort:\n");
    for (int i = 0; i < sizeQuick; i++) {
        printEmployee(&employeesQuick[i]);
    }

    // Write sorted employees to a file for Quick Sort
    writeEmployeesToFile("sorted_employees_quick.txt", employeesQuick, sizeQuick);

    // Display comparison results
    printf("\nComparison Results:\n");
    printf("Merge Sort Comparisons: %d\n", mergeSortComparisons);
    printf("Quick Sort Comparisons: %d\n", quickSortComparisons);

    return 0;
}
