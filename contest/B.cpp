#include <iostream>
#include <deque>
#include <sstream>

struct numchar {
    char ch;
    int position;
};

int main() {

    std::deque<struct numchar> line = {{0}};
    char cur_char;
    bool is_capital;
    int numerator = 1;
    std::stringstream ss;

    while (std::cin >> cur_char) {
        is_capital = cur_char - 'Z' <= 0;


        if (abs(cur_char - line.back().ch) == 32) {
            if (is_capital) {
                line.pop_back();
                ss << numerator++ << " ";
            } else {
                struct numchar last = line.back();
                line.pop_back();
                ss << last.position << " ";
            }
        } else {
            if (is_capital)
                line.push_back({cur_char, numerator++});
            else
                line.push_back({cur_char, 0});
        }
    }

    if (line.size() == 1) {
        std::cout << "Possible" << std::endl;
        std::cout << ss.str();
    } else
        std::cout << "Impossible";
}
