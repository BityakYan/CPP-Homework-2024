#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void writeRandomNumbersToFile(const std::string& filename, int count) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 1000000);

    for (int i = 0; i < count; ++i) {
        file << distr(gen) << std::endl;
    }

    file.close();
}

int partition(std::vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void _quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        _quickSort(arr, low, pi - 1);
        _quickSort(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int> &arr){
    _quickSort (arr, 0, arr.size());
}

void bubbleSort(std::vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Меняем элементы местами
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int main() {
    std::string filename = "true_randoms.txt";
    std::ifstream file(filename);
    std::vector<int> numbers;
    int num = 0;

    while (!file.eof()) {
        file>>num;
        numbers.push_back (num);
    }
    file.close();

    std::vector<int> numbers2 (numbers);

    auto start_time = std::chrono::high_resolution_clock::now();
    quickSort (numbers);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto quick = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Quicksort время: " << quick.count() << " микросекунд" << std::endl;
    
    start_time = std::chrono::high_resolution_clock::now();
    bubbleSort (numbers2);
    end_time = std::chrono::high_resolution_clock::now();
    auto bubble = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Пузырьковая сортировка время первое: " << bubble.count() << " микросекунд" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    bubbleSort (numbers2);
    end_time = std::chrono::high_resolution_clock::now();
    bubble = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Пузырьковая сортировка время второе: " << bubble.count() << " микросекунд" << std::endl;

    return 0;
}
