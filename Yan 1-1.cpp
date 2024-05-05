#include <iostream>
#include <vector>
#include <string>

template<typename T>
void Print(const T& con, const std::string& sep) {
    bool isFirst = true;

    for (const auto& item : con) {
        if (!isFirst) {
            std::cout << sep;
        }
        std::cout << item;
        isFirst = false;
    }
    
    std::cout << '\n';
}

int main() {
    std::vector<int> data = {1, 2, 3};
    Print(data, ", ");
    return 0;
}