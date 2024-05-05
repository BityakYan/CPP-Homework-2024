#include <iostream>
#include <list>

void insertion(std::list<int>& list, int number) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (*it > number) {
            list.insert(it, number);
            return;
        }
    }
    list.push_back(number);
}

int main() {
    std::list<int> original = {-5, 2, 3, -1, 0, 8, -4, 7};
    std::list<int> positive;
    std::list<int> negative;

    for (int el : original) {
        if (el >= 0) {
            insertion(positive, el);
        } else {
            insertion(negative, el);
        }
    }

    std::cout << "Positive: ";
    for (int num : positive) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Negative: ";
    for (int num : negative) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}