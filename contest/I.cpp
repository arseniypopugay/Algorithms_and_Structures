#include <vector>
#include <iostream>
#include <deque>
#include <set>

using namespace std;

//vector<int> cash;
set<pair<int, int>> delete_list;


int main() {
    int N, K, P, t;
    cin >> N >> K >> P;

    vector<int> cars;

    cars.reserve(P);
//    cash.reserve(K);
    vector<deque<int>> positions(N+1);

    for (int i = 0; i < P; i++) {
        cin >> t;
        cars.emplace_back(t);
        positions[t].push_back(i);
    }

    int hit = 0;
    for (int i = 0; i < cars.size(); i++) {

        positions[cars[i]].pop_front();

        auto it = delete_list.begin();
        for (it; it != delete_list.end(); it++) {
            if (it->second == cars[i])
                break;
        }
        if (it!=delete_list.end()) {
            delete_list.erase(it);
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, cars[i]});
            else
                delete_list.insert({positions[cars[i]].front(), cars[i]});
            hit++;
            continue;
        }

        if (delete_list.size() < K) {
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, cars[i]});
            else
                delete_list.insert({positions[cars[i]].front(), cars[i]});
        }

        else {
            --it;
            delete_list.erase(it);
            if (positions[cars[i]].empty())
                delete_list.insert({2*P, cars[i]});
            else
                delete_list.insert({positions[cars[i]].front(), cars[i]});
        }
    }
    cout << cars.size() - hit << endl;
    return 0;
}