#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <chrono>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    std::shared_ptr<Node<T>> left, right, parent;

    Node(T data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
public:
    RedBlackTree() : root(nullptr) {}

    void insert(const T& data) {
        auto newNode = std::make_shared<Node<T>>(data);
        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
        } else {
            auto current = root;
            while (current != nullptr) {
                newNode->parent = current;
                if (newNode->data < current->data) {
                    if (current->left != nullptr) current = current->left;
                    else {
                        current->left = newNode;
                        break;
                    }
                } else {
                    if (current->right != nullptr) current = current->right;
                    else {
                        current->right = newNode;
                        break;
                    }
                }
            }
            fixViolation(newNode);
        }
    }

    std::shared_ptr<Node<T>> find(const T& data) {
        auto current = root;
        while (current != nullptr) {
            if (data == current->data) {
                return current;
            } else if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }
    

private:
    std::shared_ptr<Node<T>> root;

    void rotateLeft(std::shared_ptr<Node<T>>& x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(std::shared_ptr<Node<T>>& x) {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixViolation(std::shared_ptr<Node<T>>& k) {
        std::shared_ptr<Node<T>> parent = nullptr;
        std::shared_ptr<Node<T>> grandparent = nullptr;

        while ((k != root) && (k->color != BLACK) &&
               (k->parent->color == RED)) {

            parent = k->parent;
            grandparent = k->parent->parent;

            if (parent == grandparent->left) {
                auto uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    k = grandparent;
                } else {
                    if (k == parent->right) {
                        rotateLeft(parent);
                        k = parent;
                        parent = k->parent;
                    }

                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    k = parent;
                }
            } else {
                auto uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    k = grandparent;
                } else {
                    if (k == parent->left) {
                        rotateRight(parent);
                        k = parent;
                        parent = k->parent;
                    }

                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    k = parent;
                }
            }
        }

        root->color = BLACK;
    }
};
template <typename T>
class myVector {
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    myVector() : data(nullptr), capacity(0), size(0) {}

    ~myVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }

    T& operator[](size_t index) {
        if (index > size) std::cout << "out of bound"; 
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t find(const T& value) const {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return size + 1;
    }

private:
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : 2 * capacity;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};



int main() {
    std::string filename = "true_randoms.txt";
    std::ifstream file(filename);
    
    int num = 0;
    RedBlackTree<int> tree;
    myVector<int> numbers;

    for (int i=0; i < 8010; i++) {
        file>>num;
        numbers.push_back (num);
        tree.insert(num);
    }

    std::cout << numbers.find (36736) << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i=0; i < 10000; i++)
        tree.find (36736).get();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "КЧД время: " << time.count() << " микросекунд" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    for (int i=0; i < 10000; i++)
        numbers[numbers.find (36736)];
    end_time = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Вектор время: " << time.count() << " микросекунд" << std::endl;


    file.close();
}
