#include <iostream>
#include <vector>

#define INFINITY 1000000;

using namespace std;

vector<int> numbers;
vector<int> tree;

void build_tree(int cur, int Lm, int Rm) {
    if (Lm == Rm)
        tree[cur] = numbers[Lm];
    else {
        build_tree(cur*2, Lm, (Lm+Rm)/2);
        build_tree(cur*2+1, (Lm+Rm)/2 + 1, Rm);
        tree[cur] = min(tree[2*cur], tree[2*cur + 1]);
    }
}


int get_min(int cur, int Lm, int Rm, int l, int r)
{
    if (Lm > r || Rm < l)
        return INFINITY;
    if (l <= Lm && Rm <= r)
        return tree[cur];

    return min(get_min(cur*2, Lm, (Lm+Rm)/2, l, r), get_min(cur*2+1, (Lm+Rm)/2+1, Rm, l, r));
}

int main() {

    int N, k, t;

    std::cin >> N >> k;

    numbers.reserve(N);
    tree.assign(4 * N, 0);

    for (int i = 0; i < N; i++) {
        std::cin >> t;
        numbers.push_back(t);
    }

    build_tree(1, 0, N-1);

    for (int i = 0; i<= N-k; i++)
    {
        cout << get_min(1, 0, N-1, i, i+k-1) << " ";
    }


}