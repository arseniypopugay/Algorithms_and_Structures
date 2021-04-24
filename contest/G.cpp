#include <iostream>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char, uint32_t> weights;

int main(){

    std::string input_string;
    std::string weight_string;
    std::string reminder;
    uint32_t weight;
    int letter_counter;

    std::cin >> input_string;
    for (int i = 0; i < 26; i++) {
        std::cin >> weight;
        weights['a' + i] = weight;

        letter_counter = std::count(input_string.begin(), input_string.end(), 'a'+i);
        if (letter_counter == 0) continue;
        if (letter_counter >= 2) {
            if (letter_counter > 2)
                reminder += ('a'+i)*(letter_counter-2);
            weight_string += ('a'+i);
        }
        else reminder += ('a'+i)*(letter_counter);
    }

    std::sort(weight_string.rbegin(), weight_string.rend(), [](const auto& x, const auto& y)->bool {
        return weights[x] < weights[y];
    });

    std::cout << weight_string << reminder;
    std::reverse(weight_string.begin(), weight_string.end());
    std::cout << weight_string;
}