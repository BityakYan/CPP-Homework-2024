#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

class GenealogyTree {
private:
    std::map<std::string, int> tree;

public:
    GenealogyTree(const std::string& name) {
        tree[name] = 0;
    }

    // Добавление потомка
    bool addRelation(const std::string& child, const std::string& parent) {
        auto it = tree.find(parent);
        if (it != tree.end()) {
            tree[child] = it->second + 1;
            return true;
        } else {
            std::cerr << "Родитель с именем \"" << parent << "\" не найден в древе.\n";
            return false;
        }
    }

    void printSorted() {
        for (const auto& pair : tree) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }
};

int main() {
    int N;
    std::cin >> N;

    std::string child, parent;

    std::cin >> child >> parent;
    GenealogyTree genealogy (parent);
    genealogy.addRelation (child, parent);

    for (int i = 1; i < N - 1; i++) {
        std::cin >> child >> parent;
        genealogy.addRelation (child, parent);
    }

    genealogy.printSorted();

    return 0;
}
