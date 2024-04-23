#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to calculate the sum of elements in an array using parallel reduction
double parallelSum(const vector<double>& arr) {
    double sum = 0.0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }

    return sum;
}

// Function to calculate the average of elements in an array using parallel reduction
double parallelAverage(const vector<double>& arr) {
    double sum = parallelSum(arr);
    return sum / arr.size();
}

int main() {
    // Example array
    vector<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Calculate sum using parallel reduction
    double sum = parallelSum(arr);
    cout << "Sum: " << sum << endl;

    // Calculate average using parallel reduction
    double avg = parallelAverage(arr);
    cout << "Average: " << avg << endl;

    return 0;
}
