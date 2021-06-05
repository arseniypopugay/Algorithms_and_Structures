#include <iostream>
#include <vector>

using namespace std;
vector<int> keys;
vector<int> visited;
int counter = 0;

void go_down(int pos, int start){
    if (visited[pos] == 0){
        visited[pos] = start;
        go_down(keys[pos], start);
    }
    else if (visited[pos] == start)
    {
        counter ++;
    }
}

int main(){
    int n;
    cin >> n;

    keys.assign(n+1, 0);
    visited.assign(n+1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> keys[i];
    }

    for (int i = 1; i <=n; i++)
    {
        if (visited[i] == 0)
            go_down(i, i);
    }
    cout << counter << endl;
}