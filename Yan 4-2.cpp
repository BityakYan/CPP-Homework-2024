#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

void quickSort(std::vector<int>& arr, int left, int right);

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);

        std::thread leftThread, rightThread;
        bool leftThreadActive = false;

        if (left < pi - 1) {
            leftThread = std::thread(quickSort, std::ref(arr), left, pi - 1);
            leftThreadActive = true;
        }
        if (pi + 1 < right) {
            quickSort(arr, pi + 1, right);
        }
        
        if (leftThreadActive) {
            if (leftThread.joinable()) {
                leftThread.join();
            }
        }
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5, 4872398, 7483, 478, 339, 0, -50, 10, 2};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
