#include <iostream>
#include <vector>

using namespace std;

struct lksh {
    int status;
    vector<int> send_to;
};

vector<lksh> guys;
bool marker = false;

void go_down(int pos, int set_status) {
    if (marker)
        return;
    guys[pos].status = set_status;

    for (auto &neib: guys[pos].send_to) {
        if (guys[neib].status == -1) {
            go_down(neib, 1 - set_status);
        } else if (set_status == guys[neib].status) {
            marker = true;
            return;
        }
    }
}

int main() {
    int N, M, a, b;
    cin >> N >> M;
    guys.reserve(N + 1);
    guys.push_back({});
    for (int i = 1; i <= N; i++) {
        guys.push_back({-1});
    }

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        guys[a].send_to.push_back(b);
        guys[b].send_to.push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        if (guys[i].status == -1)
            go_down(i, 0);
        if (marker)
            break;
    }

    if (marker)
        cout << "NO";
    else
        cout << "YES";
}