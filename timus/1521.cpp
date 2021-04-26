#include <iostream>

struct Node {
    int lowest; //0 if not lowest
    int below;
    Node *left;
    Node *right;

    Node(int b) {
        lowest = 0;
        below = b;
        left = nullptr;
        right = nullptr;
    }
};

void build_tree(struct Node *root, int start_with) {
    if (root->below == 0) {
        root->lowest = start_with;
        return;
    }
    if (root->below >= 2) {
        root->left = new Node(root->below / 2);
        build_tree(root->left, start_with);
        root->right = new Node(root->below - root->below / 2);
        build_tree(root->right, start_with + root->below / 2);
    }
    if (root->below == 1) {
        root->left = new Node(0);
        build_tree(root->left, start_with);
    }
}

void print_tree(struct Node *root) {
    if (!root)
        return;
    if (root->lowest) {
        std::cout << root->lowest << ' ';
        return;
    }

    if (root->below == 0)
        return;
    else {
        print_tree(root->left);
        print_tree(root->right);
    }
}

void remove_from_tree(struct Node *root, int k) {


    if (root->lowest) {
        std::cout << root->lowest << ' ';
        return;
    }

    if (root->left && (root->left->below >= k || root->left->lowest)) {
        remove_from_tree(root->left, k);
        root->below--;
        return;
    }

    if (root->right) {
        remove_from_tree(root->right, k - root->left->below);
        root->below--;
        return;
    }
}

int main() {

    int n, k, delete_number = 1;

    std::cin >> n >> k;

    auto root = new Node(n);
    build_tree(root, 1);

    while (root->below != 0) {
        delete_number = delete_number + k - 1;

        if (delete_number % root->below)
            delete_number = delete_number % root->below;
        else
            delete_number = root->below;

        remove_from_tree(root, delete_number);
    }
}