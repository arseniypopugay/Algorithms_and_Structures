#include <iostream>
#include <deque>
#include <algorithm>

int main(){

    std::deque<int> window;
    int N, k, t;

    std::cin >> N >> k;

    for (int i = 0; i < k; i++)
    {
        std::cin >> t;
        window.push_back(t);
    }

    std::sort(window.begin(), window.end());
    std::cout << window.front();

    for (auto &el: window)
        std::cout << el << " ";

}