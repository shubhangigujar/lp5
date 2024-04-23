#include <iostream>
#include <vector>
#include <chrono>

// Function to perform bubble sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallelized bubble sort using OpenMP
void parallelBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    int i, j;
    #pragma omp parallel for private(i, j) shared(arr)
    for (i = 0; i < n - 1; ++i) {
        for (j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    // Generating random input array
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    // Measure sequential performance
    auto startSeq = std::chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seqDuration = endSeq - startSeq;

    // Print sorted array and sequential time
    std::cout << "Sorted array (sequential): ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Sequential time: " << seqDuration.count() << " seconds" << std::endl;

    // Generate random input array again for parallel sort
    arr = {12, 11, 13, 5, 6, 7};

    // Measure parallel performance
    auto startParallel = std::chrono::high_resolution_clock::now();
    parallelBubbleSort(arr);
    auto endParallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> parallelDuration = endParallel - startParallel;

    // Print sorted array and parallel time
    std::cout << "Sorted array (parallel): ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Parallel time: " << parallelDuration.count() << " seconds" << std::endl;

    return 0;
}


