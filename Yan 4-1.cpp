#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <algorithm>

void find_max_elements(std::vector<int>& nums, int begin, int end, std::vector<int>& local_max) {
    local_max.resize(3, std::numeric_limits<int>::min());

    for (int i = begin; i < end; ++i) {
        if (nums[i] > local_max[0]) {
            local_max[2] = local_max[1];
            local_max[1] = local_max[0];
            local_max[0] = nums[i];
        } else if (nums[i] > local_max[1]) {
            local_max[2] = local_max[1];
            local_max[1] = nums[i];
        } else if (nums[i] > local_max[2]) {
            local_max[2] = nums[i];
        }
    }
}

int main() {
    const int N = 1000000;
    std::vector<int> nums(N);

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(1, 1000000);

    for (int& num : nums) {
        num = distr(eng);
    }

    int thread_count = 4;
    std::vector<std::thread> threads;
    std::vector<std::vector<int>> max_elements(thread_count, std::vector<int>(3, std::numeric_limits<int>::min()));

    int size_per_thread = N / thread_count;

    for (int i = 0; i < thread_count; ++i) {
        int begin = i * size_per_thread;
        int end = (i + 1) == thread_count ? N : (i + 1) * size_per_thread;
        threads.emplace_back(find_max_elements, std::ref(nums), begin, end, std::ref(max_elements[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::vector<int> global_max(3, std::numeric_limits<int>::min());
    for (auto& local_max : max_elements) {
        for (int i = 0; i < 3; ++i) {
            if (local_max[i] > global_max[0]) {
                global_max[2] = global_max[1];
                global_max[1] = global_max[0];
                global_max[0] = local_max[i];
            } else if (local_max[i] > global_max[1]) {
                global_max[2] = global_max[1];
                global_max[1] = local_max[i];
            } else if (local_max[i] > global_max[2]) {
                global_max[2] = local_max[i];
            }
        }
    }

    int sum_of_largest = global_max[0] + global_max[1] + global_max[2];
    std::cout << "Сумма: " << sum_of_largest << std::endl;

    return 0;