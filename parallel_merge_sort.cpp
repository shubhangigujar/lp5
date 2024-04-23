#include <iostream>
#include <vector>
#include <chrono>

void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortSequential(std::vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSortSequential(arr, l, m);
    mergeSortSequential(arr, m + 1, r);
    merge(arr, l, m, r);
}

void mergeSortParallel(std::vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    
    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(arr, l, m);
        #pragma omp section
        mergeSortParallel(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    // Sequential Merge Sort
    auto start_seq = std::chrono::high_resolution_clock::now();
    mergeSortSequential(arr, 0, n - 1);
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq = end_seq - start_seq;

    std::cout << "Sorted array using sequential merge sort:\n";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << "\nSequential merge sort duration: " << duration_seq.count() << " seconds\n";

    // Parallel Merge Sort
    std::vector<int> arr_parallel = {12, 11, 13, 5, 6, 7}; // Reset array
    auto start_parallel = std::chrono::high_resolution_clock::now();
    mergeSortParallel(arr_parallel, 0, n - 1);
    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_parallel = end_parallel - start_parallel;

    std::cout << "\nSorted array using parallel merge sort:\n";
    for (int i = 0; i < n; i++)
        std::cout << arr_parallel[i] << " ";
    std::cout << "\nParallel merge sort duration: " << duration_parallel.count() << " seconds\n";

    return 0;
}

