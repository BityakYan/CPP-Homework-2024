#include <iostream>
#include <sstream>
#include <map>
#include <string>

int main() {
    std::string text = "qwe 123 123 qw qw tr tr qw aw";

    std::map<std::string, int> word_count;
    std::string word;
    std::istringstream stream(text);

    std::string most_frequent_word;
    int max_count = 0;

    while (stream >> word) {
        int current_count = ++word_count[word];
        if (current_count > max_count || (current_count == max_count && word < most_frequent_word)) {
            most_frequent_word = word;
            max_count = current_count;
        }
    }

    std::cout << most_frequent_word << std::endl;

    return 0;
}
