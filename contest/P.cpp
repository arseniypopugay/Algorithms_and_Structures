#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> field;
vector<bool> visited;


void visit(int ver, bool is_forward, int size) {
    visited[ver] = true;
    for (int i = 0; i < field.size(); i++) {
        if (visited[i]) continue;
        if (is_forward) {
            if (field[i][ver] <= size) {
                visit(i, is_forward, size);
            }
        } else {
            if (field[ver][i] <= size) {
                visit(i, is_forward, size);
            }
        }
    }
}


bool check(int size) {
    visited.assign(visited.size(), false);
    visit(0, true, size);
    if (std::all_of(visited.begin(), visited.end(), [](bool v) { return v; }))
    {
        visited.assign(visited.size(), false);
        visit(0, false, size);
        return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
    }
    return false;
}

int main() {
    int N, l = 0, r = 0;
    cin >> N;

    field.assign(N, vector<int>(N));
    visited.assign(N, false);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> field[i][j];
            r = max(r, field[i][j]);
        }

    while (l < r) {
        if (check((l + r) / 2)) {
            r = (l + r) / 2;
        } else {
            l = (l + r) / 2 + 1;
        }
    }

    cout << l;
}
