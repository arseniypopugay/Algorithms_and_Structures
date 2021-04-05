#include <iostream>

int main() {
    int n;
    int p;
    long cur_sum = 0;
    long best_sum = 0;

    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> p;
        cur_sum = cur_sum > -p ? cur_sum + p : 0; //max(0, cur_sum + p);
        best_sum = cur_sum > best_sum ? cur_sum : best_sum; //max(cur_sum, best_sum);
    }

    std::cout << best_sum;
}