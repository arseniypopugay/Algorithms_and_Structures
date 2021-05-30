#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct block {
    int num;
    int size;
    struct block *left;
    struct block *right;
    bool free;
};

struct CmpBlocks {
    bool operator()(const block *a, const block *b) const {
        if (a->size == b->size)
            return a->num < b->num;
        return a->size < b->size;
    }
};

set<struct block *, CmpBlocks> free_blocks;
vector<struct block *> requests;

void merge_chain_elem(block *a, block *b) {
    a->size += b->size;
    a->right = b->right;
    if (b->right) {
        b->right->left = a;
    }
    delete b;
}

int main() {
    int N, M, input;
    cin >> N >> M;
    requests.reserve(M);

    auto t = new block{1, N, nullptr, nullptr, true};
    free_blocks.insert(t);

    for (int i = 0; i < M; i++) {
        cin >> input;

        if (input > 0) {
            if (free_blocks.empty()) {
                requests.push_back(nullptr);
                cout << -1 << endl;
                continue;
            }

            auto it = free_blocks.end();
            it--;


            if ((*it)->size < input) {
                requests.push_back(nullptr);
                cout << -1 << endl;
                continue;
            }

            if ((*it)->size == input) {
                (*it)->free = false;
                cout << (*it)->num << endl;
                requests.push_back(*it);
                free_blocks.erase(it);
                continue;
            }


            auto leftover = new block{(*it)->num + input, (*it)->size - input, *it, (*it)->right, true};
            if ((*it)->right){
                (*it)->right->left = leftover;
            }

            (*it)->right = leftover;
            (*it)->size = input;
            (*it)->free = false;
            cout << (*it)->num << endl;

            requests.push_back(*it);
            free_blocks.erase(it);
            free_blocks.insert(leftover);


        } else {
            requests.push_back(nullptr);
            auto el = requests[(-input) - 1];
            requests[(-input) - 1] = nullptr;
            if (!el) continue;
            el->free = true;

            if (el->left && el->left->free){
                free_blocks.erase(el->left);
                el = el->left;
                merge_chain_elem(el, el->right);
            }

            if (el->right && el->right->free){
                free_blocks.erase(el->right);
                merge_chain_elem(el, el->right);
            }

            free_blocks.insert(el);
        }
    }

    return 0;
}