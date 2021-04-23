#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::string input_line;
    std::vector<std::string> strs;

    while(std::cin >> input_line)
        strs.emplace_back(input_line);

    std::sort(strs.rbegin(), strs.rend(), [](const auto& x, const auto& y)->bool {
        return x+y<y+x;
    });

    for (auto &str: strs)
        std::cout << str;
    std::cout << std::endl;
}
