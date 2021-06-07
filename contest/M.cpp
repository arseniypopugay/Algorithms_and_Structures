#include <iostream>
#include <set>
#include <vector>
#include <stack>

#define inf 3000000
using namespace std;

struct point {
    int cost;
    int dist;
    int x;
    int y;
    int prev; // North = 0, East = 1, South = 2, West = 3;
    pair<int, int> prev_cords;
};

//auto p_hash = [](const point& n){ return std::hash<std::string>()(to_string(10000*n.x+n.y)); };
//auto p_equal = [](const point& n1, const point& n2){ return (n1.x == n2.x) && (n1.y==n2.y); };



vector<set<pair<int, int>>> waves(2);
int wave_switcher = 0;
struct point map[1001][1001];

void wave(int field_size_x, int field_size_y) {
    waves[1 - wave_switcher].clear();

    for (auto &p: waves[wave_switcher]) {
        auto el = map[p.first][p.second];
        if (el.x != 1 && map[el.x - 1][el.y].cost != -1 &&
            map[el.x - 1][el.y].dist > el.dist + map[el.x - 1][el.y].cost) {
            map[el.x - 1][el.y].dist = el.dist + map[el.x - 1][el.y].cost;
            map[el.x - 1][el.y].prev = 0;
            map[el.x - 1][el.y].prev_cords = p;
//                waves[1-wave_switcher].insert(map[el.x-1][el.y]);
            waves[1 - wave_switcher].insert({p.first - 1, p.second});
        }
        if (el.x != field_size_x && map[el.x + 1][el.y].cost != -1 &&
            map[el.x + 1][el.y].dist > el.dist + map[el.x + 1][el.y].cost) {
            map[el.x + 1][el.y].dist = el.dist + map[el.x + 1][el.y].cost;
            map[el.x + 1][el.y].prev = 2;
            map[el.x + 1][el.y].prev_cords = p;
//            waves[1-wave_switcher].insert(map[el.x+1][el.y]);
            waves[1 - wave_switcher].insert({p.first + 1, p.second});
        }

        if (el.y != 1 && map[el.x][el.y - 1].cost != -1 &&
            map[el.x][el.y - 1].dist > el.dist + map[el.x][el.y - 1].cost) {
            map[el.x][el.y - 1].dist = el.dist + map[el.x][el.y - 1].cost;
            map[el.x][el.y - 1].prev = 3;
            map[el.x][el.y - 1].prev_cords = p;
//            waves[1-wave_switcher].insert(map[el.x][el.y-1]);
            waves[1 - wave_switcher].insert({p.first, p.second - 1});
        }
        if (el.y != field_size_y && map[el.x][el.y + 1].cost != -1 &&
            map[el.x][el.y + 1].dist > el.dist + map[el.x][el.y + 1].cost) {
            map[el.x][el.y + 1].dist = el.dist + map[el.x][el.y + 1].cost;
            map[el.x][el.y + 1].prev = 1;
            map[el.x][el.y + 1].prev_cords = p;

//            waves[1-wave_switcher].insert(map[el.x][el.y+1]);
            waves[1 - wave_switcher].insert({p.first, p.second + 1});
        }
    }

    wave_switcher = 1 - wave_switcher;
}

int main() {
    int N, M, x0, y0, xt, yt;
    char temp;
    cin >> N >> M >> x0 >> y0 >> xt >> yt;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> temp;
            switch (temp) {
                case '.':
                    map[i][j] = {1, inf, i, j, -1};
                    break;
                case 'W':
                    map[i][j] = {2, inf, i, j, -1};
                    break;
                default: //temp == W
                    map[i][j] = {-1, inf, i, j, -1};
                    break;
            }
        }
    }

    map[x0][y0].dist = 0;
    waves[wave_switcher].insert({x0, y0});
    while (!waves[wave_switcher].empty()) {
        wave(N, M);
//        cout << "wave" << endl;
    };

//
//    for (int i = 1; i <= N; i++) {
//        for (int j = 1; j <= M; j++) {
//            cout << map[i][j].dist << "   ";
//        }
//        cout << endl;
//    }
//
//    cout << endl << endl << endl;
//
//    for (int i = 1; i <= N; i++) {
//        for (int j = 1; j <= M; j++) {
//            cout << map[i][j].prev << "   ";
//        }
//        cout << endl;
//    }

    if (map[xt][yt].dist == inf){
        cout << -1;
        return 0;
    }

    cout << map[xt][yt].dist << endl;

    stack<char> path;
    pair<int, int> p = {xt, yt};
    while (!(p.first == x0 && p.second == y0)){
        switch (map[p.first][p.second].prev) {
            case 0:
                path.push('N');
                break;
            case 1:
                path.push('E');
                break;
            case 2:
                path.push('S');
                break;
            default:
                path.push('W');
                break;
        }
        p = map[p.first][p.second].prev_cords;
    }
    while (!path.empty()){
        cout << path.top();
        path.pop();
    }
}