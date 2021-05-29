#include <vector>
#include <iostream>
#include <deque>
#include <set>

using namespace std;

vector<int> cash;
set<pair<int, int>> delete_list;

int search(int num) {
    for (int i = 0; i < cash.size(); i++)
        if (cash[i] == num) return i;
    return -1;
}

int main() {
    int N, K, P, t;
    cin >> N >> K >> P;

    vector<int> cars;

    cars.reserve(P);
    cash.reserve(K);
    vector<deque<int>> positions(N+1);

    for (int i = 0; i < P; i++) {
        cin >> t;
        cars.emplace_back(t);
        positions[t].push_back(i);
    }

    int hit = 0;
    for (int i = 0; i < cars.size(); i++) {

        positions[cars[i]].pop_front();

        int r = search(cars[i]);
        if (r!=-1) {
            delete_list.erase({i, r});
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, r});
            else
                delete_list.insert({positions[cars[i]].front(), r});
            hit++;
            continue;
        }

        if (cash.size() < K) {
            cash.push_back(cars[i]);
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, cash.size()-1});
            else
                delete_list.insert({positions[cars[i]].front(), cash.size()-1});
        }

        else {
            auto it = delete_list.end();
            int j = (*--it).second;
            delete_list.erase(it);
            cash[j] = cars[i];
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, j});
            else
                delete_list.insert({positions[cars[i]].front(), j});
        }
    }
    cout << cars.size() - hit << endl;
    return 0;
}