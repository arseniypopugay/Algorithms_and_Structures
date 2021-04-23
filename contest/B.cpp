#include <iostream>
#include <deque>
#include <vector>

struct numchar {
    char ch;
    size_t position;
};

int main() {

    std::deque<struct numchar> line = {{0}};
    char cur_char;
    bool is_capital;
    size_t animal_number = 1;
    std::vector<size_t> cage_positioner;

    while (std::cin >> cur_char) {
        is_capital = cur_char - 'Z' <= 0;


        if (abs(cur_char - line.back().ch) == 32) {
            if (!is_capital) {
                struct numchar last = line.back();
                line.pop_back();
                cage_positioner[last.position] = animal_number++;
            } else {
                struct numchar last = line.back();
                line.pop_back();
                cage_positioner.push_back(last.position);
            }
        } else {
            if (!is_capital) {
                line.push_back({cur_char, animal_number++});
            } else {
                cage_positioner.push_back(0);
                line.push_back({cur_char, cage_positioner.size()-1});
            }
        }
    }

    if (line.size() == 1) {
        std::cout << "Possible" << std::endl;
        for (auto &el: cage_positioner)
            std::cout << el << " ";
    } else
        std::cout << "Impossible";
}
