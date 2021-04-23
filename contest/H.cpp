#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n, k, t;
    int sum = 0;
    std::vector<int> goods;

    std::cin >> n >> k;
    for (int i=0; i<n; i++){
        std::cin >> t;
        goods.emplace_back(t);
    }

    std::sort(goods.rbegin(), goods.rend());

    for (int i = 0; i < n/k; i++)
        for (int j = 0; j<k-1; j++)
            sum += goods[i*k + j];

    for (int i = 0; i<n%k; i++)
        sum += goods[k*(n/k)+i];

    std::cout << sum;
}