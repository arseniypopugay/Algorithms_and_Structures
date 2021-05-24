#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<stack>

using namespace std;

int weights[10];
int I = 0;

struct node {
    int number;
    int next;
    int weight;
    node(int number, int next, int weight)
    {
        this->number = number;
        this->weight = weight;
        this->next = next;
    }
};
vector<node> side;
map<string, int> telegraph_position;
vector<string> s;
stack<int> st;
vector<int> previ;
vector<int> head;
vector<int> dist;
vector<bool> visited;

void add(int i, int j, int weight) {
    side.emplace_back(j, head[i], weight);
    head[i] = I++;
}

int costtime(int i, int j) {
    for (int x = 0; x < 10; ++x) {
        if (s[i][x] != s[j][x])
            return weights[x];
    }
    return 10;
}

bool dijkstra(int start, int end) {
    queue<int> qt;
    qt.push(start);
    visited[start] = true;
    dist[start] = 0;

    while (!qt.empty()) {
        int x = qt.front();
        qt.pop();
        visited[x] = false;
        for (int t = head[x]; t != -1; t = side[t].next) {
            int j = side[t].number;
            if (dist[j] == -1 || dist[j] > dist[x] + side[t].weight) {

                dist[j] = dist[x] + side[t].weight;
                previ[j] = x;
                if (!visited[j]) {
                    visited[j] = true;
                    qt.push(j);
                }
            }
        }
    }

    if (dist[end] == -1)
        return false;
    return true;
}

int main() {
    int n;
    cin >> n;
    string a;

    for (int &weight : weights)
        cin >> weight;

    s.emplace_back(a);
    for (int i = 0; i < n; ++i) {
        cin >> a;
        s.push_back(a);
        telegraph_position[a] = i + 1;
    }

    head.assign(n + 1, -1);
    dist.assign(n + 1, -1);
    visited.assign(n + 1, false);
    previ.assign(n + 1, -1);

    map<string, int>::iterator it;

    for (int i = 1; i <= n; ++i) {
        s[0] = s[i];

        for (int l = 0; l < 10; ++l) {
            char cur_char = s[i][l];
            for (char c = '0'; c <= '9'; ++c) {
                if (cur_char == c)
                    continue;
                s[i][l] = c;
                if ((it = telegraph_position.find(s[i])) != telegraph_position.end()) {
                    add(i, it->second, costtime(0, it->second));
                }
            }
            s[i][l] = cur_char;
        }


        for (int l = 0; l < 10; ++l)
            for (int r = l + 1; r < 10; ++r) {
                if (s[i][l] == s[i][r])
                    continue;
                swap(s[i][l], s[i][r]);
                if ((it = telegraph_position.find(s[i])) != telegraph_position.end()) {
                    add(i, it->second, costtime(0, it->second));
                }
                swap(s[i][l], s[i][r]);
            }
    }


    if (!dijkstra(1, n)) {
        cout << "-1";
        return 0;
    }

    int k = n;
    while (k != 1) {
        st.push(k);
        k = previ[k];
    }

    cout << dist[n] << endl << (st.size() + 1) << endl << "1";

    while (!st.empty()) {
        cout << " " << st.top();
        st.pop();
    }
    cout << endl;
}
