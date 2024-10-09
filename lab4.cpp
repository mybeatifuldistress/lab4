#include <iostream>
#include <memory>
#include <string>

int C;
int R;

void FindTree(struct Node* root, int data);
struct Node* CreateTree(struct Node* root, struct Node* r, int data);
int FindLevel(Node* root, int data, int level = 0);
void print_tree(struct Node* r, int l);
Node* DeleteNode(Node* root, int data);
Node* FindMin(Node* node);

struct Node {
    int data;
    Node* left;
    Node* right;
};

int main() {
    std::setlocale(LC_ALL, "");
    std::string input;
    int D;

    Node* root = nullptr;
    std::cout << "Введите (*) для окончания построения дерева" << std::endl;
    while (true) {
        std::cout << "Введите число: ";
        std::cin >> input;
        if (input == "*") {
            std::cout << "Построение дерева окончено" << std::endl << std::endl;
            break;
        }
        D = std::stoi(input);
        C = 0; R = 0;
        FindTree(root, D);
        if (C == 0) {
            root = CreateTree(root, root, D);
        }
        else {
            std::cout << "Введите другое число, отличное от этого" << std::endl;
        }
        print_tree(root, 0);
    }

    std::cout << "Введите (*) для окончания поиска" << std::endl;
    while (true) {
        std::cout << "Введите искомое число: ";
        std::cin >> input;
        if (input == "*") {
            std::cout << "Поиск окончен" << std::endl << std::endl;
            break;
        }
        D = std::stoi(input);
        C = 0; R = 0;
        FindTree(root, D);
        std::cout << "Число вхождений = " << C << std::endl;
        std::cout << "Сложность поиска = " << R << std::endl;

        int level = FindLevel(root, D);
        if (level != -1) {
            std::cout << "Уровень элемента " << D << " = " << level << std::endl;
        }
        else {
            std::cout << "Элемент " << D << " не найден в дереве" << std::endl;
        }
    }

    while (true) {
        std::cout << "Введите число для удаления (* для выхода): ";
        std::cin >> input;
        if (input == "*") break;
        D = std::stoi(input);
        root = DeleteNode(root, D);
        print_tree(root, 0);
    }

    return 0;
}

void FindTree(Node* root, int data) {
    R++;
    if (root == nullptr) return;

    if (data == root->data) {
        C++;
    }

    if (data < root->data) {
        FindTree(root->left, data);
    }
    else {
        FindTree(root->right, data);
    }
}

Node* CreateTree(Node* root, Node* r, int data) {
    if (r == nullptr) {
        r = new Node;
        if (r == nullptr) {
            std::cerr << "Ошибка выделения памяти" << std::endl;
            std::exit(1);
        }

        r->left = nullptr;
        r->right = nullptr;
        r->data = data;
        if (root == nullptr) return r;

        if (data < root->data) root->left = r;
        else root->right = r;
        return r;
    }

    if (data < r->data) {
        CreateTree(r, r->left, data);
    }
    else {
        CreateTree(r, r->right, data);
    }

    return root;
}

int FindLevel(Node* root, int data, int level) {
    if (root == nullptr) {
        return -1;
    }

    if (root->data == data) {
        return level;
    }

    int leftLevel = FindLevel(root->left, data, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }

    int rightLevel = FindLevel(root->right, data, level + 1);
    return rightLevel;
}

void print_tree(Node* r, int l) {
    if (r == nullptr) {
        return;
    }

    print_tree(r->right, l + 1);
    std::cout << l << "-";
    for (int i = 0; i < l; i++) {
        std::cout << "  ";
    }

    std::cout << r->data << std::endl;
    print_tree(r->left, l + 1);
}

Node* DeleteNode(Node* root, int data) {
    if (root == nullptr) {
        return root;
    }

    if (data < root->data) {
        root->left = DeleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = DeleteNode(root->right, data);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = FindMin(root->right);
        root->data = temp->data;
        root->right = DeleteNode(root->right, temp->data);
    }
    return root;
}

Node* FindMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
