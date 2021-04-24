#include <iostream>
#include <vector>

struct sign {
    int quantity;
    int number;
};

int main() {
    int k, q, sum = 0;
    std::cin >> k;

    std::vector<struct sign> s;
    s.reserve(k);

    for (int i = 1; i <= k; i++) {
        std::cin >> q;
        s.push_back({q, i});
        sum += q;
    }

    struct sign prev{}, max{};

    for (int i = 0; i < sum; i++) {

        for (int j = 0; j < k; j++) {
            if (s[j].quantity >= max.quantity && s[j].number != prev.number) {
                max = s[j];
            }
        }

        if (max.quantity != 0) {
            std::cout << max.number << " ";
            s[max.number - 1].quantity -= 1;
            max.quantity = 0;
            prev = max;
        }
    }

    for (int i = 0; i < k; i++) {
        if (s[i].quantity != 0) {
            for (int j = 0; j < s[i].quantity; j++) {
                std::cout << s[i].number << ' ';
            }
        }
    }

}