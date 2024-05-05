#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

bool isValidSequence(const std::string& s) {
    std::unordered_map<char, char> matching_bracket = {{')', '('}, {'}', '{'}, {']', '['}};
    std::stack<char> stack;

    for (char ch : s) {
        if (matching_bracket.count(ch) > 0) {
            if (!stack.empty() && stack.top() == matching_bracket[ch]) {
                stack.pop();
            } else {
                return false;
            }
        } else {
            stack.push(ch);
        }
    }

    return stack.empty();
}

int main() {
    std::string sequence1 = "({[[{()()}[]{}]]})";
    std::string sequence2 = "({[[{({})(})}[]{}]]})";
    std::cout << isValidSequence(sequence1) << std::endl;
    std::cout << isValidSequence(sequence2) << std::endl;
    return 0;
}
