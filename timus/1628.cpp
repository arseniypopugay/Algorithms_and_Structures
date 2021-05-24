#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

using namespace std;


int main() {
    long N, M, K, ans = 0, x, y;
    vector<pair<long, long>> cell;
    set<pair<long, long>> singles;

    cin >> N >> M >> K;

    cell.reserve(K+2*N+2*M);

    for (long i = 0; i < K; ++i) {
        cin >> x >> y;
        cell.emplace_back(x, y);
    }

    for (long i = 1; i <= M; i++) {
        cell.emplace_back(0, i);
        cell.emplace_back(N+1, i);
        K+=2;
    }
    for (long i = 1; i <= N; i++) {
        cell.emplace_back(i, 0);
        cell.emplace_back(i, M+1);
        K+=2;
    }

    sort(cell.begin(), cell.end(), [](const auto& a, const auto& b)->bool {
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });

    for (int i = 0; i <= K ; i++) {
        if (cell[i].first == cell[i + 1].first && (cell[i + 1].second - cell[i].second) >= 2) {
            if (cell[i + 1].second - cell[i].second == 2) singles.insert({cell[i].first,cell[i].second + 1});
            else ans++;
        }
    }

    sort(cell.begin(), cell.end(), [](const auto& a, const auto& b)->bool {
        if (a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    });

    for (int i = 0; i <= K;++i) {
        if (cell[i].second == cell[i + 1].second && cell[i + 1].first - cell[i].first >= 2) {
            if (cell[i + 1].first - cell[i].first == 2) {
                if (singles.find({cell[i].first+1, cell[i].second}) != singles.end())
                    ans++;
            }
            else ans++;
        }
    }

    cout << ans;

    return 0;
}