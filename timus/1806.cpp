#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct Node;

struct Link {
    int32_t weight;
    Node *point;
};

struct Node {
    vector<Link> neighbours;
    string number;
    int32_t dist;
    Node *prev;
    size_t position;
};

bool operator<(const Node& a, const Node& b) {
    return a.dist > b.dist;
}


vector<Node *> telegraphs;
deque<Node*> Q;
int transmission_cost[10] = {0};

int calculate_cost(string n1, string n2) {
    int fail_count = 0, prefix_len = 0;
    char fail_sym1, fail_sym2;

    for (int i = 0; i < n1.length(); i++) {
        switch (fail_count) {
            case 0:
                if (n1[i] == n2[i])
                    prefix_len++;
                else {
                    fail_count++;
                    fail_sym1 = n1[i];
                    fail_sym2 = n2[i];
                }
                break;
            case 1:
                if (n1[i] != n2[i]) {
                    if (n1[i] == fail_sym2 && n2[i] == fail_sym1) {
                        fail_count++;
                    } else return -1;
                }
                break;
            case 2:
                if (n1[i] != n2[i])
                    return -1;
                break;
            default:
                return -1;

        }
    }
    return transmission_cost[prefix_len];
}

void add_number(const string& number) {
    auto node_number = new Node();
    node_number->number = number;
    node_number->dist = INT32_MAX/2;
    node_number->prev = nullptr;
    node_number->position = telegraphs.size()+1;

    for (auto& node: telegraphs)
    {
        int cost = calculate_cost(number, node->number);
        if (cost!=-1) {
            node_number->neighbours.push_back({cost, node});
            node->neighbours.push_back({cost, node_number});
        }
    }

    telegraphs.push_back(node_number);
}

int main() {
    int n;
    cin >> n;

    for (int & cost : transmission_cost)
        cin >> cost;

    for (int i = 0; i < n; i++)
    {
        string number;
        cin >> number;
        add_number(number);
    }


//    for (auto &node: telegraphs)
//    {
//        cout << node->number << ": " << endl;
//        for (auto &neigh: node->neighbours)
//            cout << "\t" << neigh.point->number << " - " << neigh.weight << endl;
//    }

    telegraphs[0]->dist = 0;


    for (auto&el: telegraphs)
        Q.push_back(el);

    while (!Q.empty()) {

        auto it = min_element(Q.begin(), Q.end(), [](const auto& x, const auto& y)->bool {
            return x->dist < y->dist;
        });
        auto v = (*it);

//        cout << "Current vertex: " << v->number  << " with dist "<<  v->dist<< endl;
        for (auto &u: v->neighbours)
        {
            int new_dist = v->dist + u.weight;
            if (new_dist < u.point->dist)
            {
                u.point->dist = new_dist;
                u.point->prev = v;
            }
        }

        Q.erase(it);
    }

//    for (auto &node: telegraphs)
//        {
//            cout << node->number << ": " << node->dist << endl;
//        }

    auto v = telegraphs.back();

    if (!v->prev)
    {
        cout << -1;
        return 0;
    }

    cout << v->dist << endl;

    deque <size_t> path;

    while (v->prev)
    {
        path.push_front(v->position);
        v = v->prev;
    }

    cout << path.size() +1 << endl << 1 << " ";
    for (auto &el: path)
        cout << el << " ";
}