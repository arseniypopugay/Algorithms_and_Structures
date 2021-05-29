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
            it --;


            if ((*it)->size < input) {
                requests.push_back(nullptr);
                cout << -1 << endl;
                continue;
            }

            if ((*it)->size == input){
                (*it)->free = false;
                cout << (*it)->num << endl;
                requests.push_back(*it);
                free_blocks.erase(it);
                continue;
            }


            auto leftover = new block{(*it)->num+input, (*it)->size - input, *it, (*it)->right, true};
            (*it)->right = leftover;
            (*it)->size = input;
            (*it)->free = false;
            cout << (*it)->num << endl;

            requests.push_back(*it);
            free_blocks.erase(it);
            free_blocks.insert(leftover);


        } else {
            requests.push_back(nullptr);
            auto el = requests[(-input)-1];
            requests[(-input)-1] = nullptr;
            if (!el) continue;
            el->free = true;

            if (el->left && el->left->free){

                auto left_elem = el->left;
                free_blocks.erase(left_elem);
                left_elem->size += el->size;
                left_elem->right = el->right;
                if (el->right)
                    el->right->left = left_elem;

                delete el;
                el = left_elem;
            }

                if (el->right && el->right->free){
                auto right_elem = el->right;
                free_blocks.erase(right_elem);
                el->right = right_elem->right;
                el->size += right_elem->size;
                if (right_elem->right)
                    right_elem->right->left = el;
                delete right_elem;
            }

//            cout << "Freeing " << el->num << endl;
            free_blocks.insert(el);
        }
    }

    return 0;
}


//int main(){
//    int N, M, p;
//    cin >> N >> M;
//
//    auto t = new block {1, N, nullptr, nullptr, true};
//    free_blocks.insert(t);
//
//    for (int i = 0; i < M; i++)
//    {
//        cin >> p;
//        if (p>0) {
//            if (free_blocks.empty()) {
//                requests.push_back(nullptr);
//                cout << -1 << endl;
//                continue;
//            }
//
//            auto it = free_blocks.end();
//            it--;
//
//            if ((*it)->size < p){
//                requests.push_back(nullptr);
//                cout << -1 << endl;
//                continue;
//            }
//            else{
//                if ((*it)->size == p)
//                {
//                    requests.push_back(*it);
//                    cout << (*it)->num << endl;
//                    (*it)->free = false;
//                    free_blocks.erase(it);
//                } else {
//                    auto leftover = new block{(*it)->num+p,(*it)->size-p, *it, (*it)->right, true};
//                    (*it)->right = leftover;
//                    (*it)->size = p;
//                    (*it)->free = false;
//                    requests.push_back(*it);
//                    cout << (*it)->num << endl;
//                    free_blocks.erase(it);
//                    free_blocks.insert(leftover);
//                }
//            }
//
//        } else {
//            requests.push_back(nullptr);
//            auto el = requests[-p-1];
//            if (!el) continue;
//            requests[-p-1] = nullptr;
//            el->free = true;
//
//            if (el->left && el->left->free)
//            {
//                auto left_el = el->left;
//                free_blocks.erase(left_el);
//                left_el->size += el->size;
//                left_el->right = el->right;
//                if (el->right) {
//                    el->right->left = left_el;
//                }
//                delete el;
//                el = left_el;
//
//            }
//
//            if (el->right && el->right->free)
//            {
//                auto right_el = el->right;
//                free_blocks.erase(right_el);
//                el->size += right_el->size;
//                el->right = right_el->right;
//                if (el->right) {
//                    el->right->left = el;
//                }
//                delete right_el;
//
//            }
////            cout << "request[-p-1] " << endl;
////            cout << "Made free block size = " << el->size << " and num = " << el->num << endl;
////            cout << "Total free blocks = " << free_blocks.size()+1 << endl;
//            cout << "Freeing " << el->num << endl;
//            free_blocks.insert(el);
////            cout << "Insertion done" << endl;
//
//        }
//    }
//
//
//}