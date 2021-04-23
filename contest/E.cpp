#include <iostream>
#include <vector>


int is_spreadable(int32_t step, int32_t k, std::vector<int32_t> positions){
    k--;
    int32_t prev_pos = positions.front();
    for (auto &coord: positions)
        if (coord-prev_pos>=step)
        {
            prev_pos = coord;
            k--;
        }

    return k<=0;
}


int main(){
    int32_t n, k, max_min_dist, min_step = INT32_MAX, t, prev_t;
    std::vector<int32_t> positions;

    std::cin >> n >> k;

    std::cin >> prev_t;
    positions.emplace_back(prev_t);

    for (int32_t i = 1; i < n; i++)
    {
        std::cin >> t;
        min_step = std::min(t-prev_t, min_step);
        prev_t = t;
        positions.emplace_back(t);
    }

    int32_t left = min_step;
    int32_t right = (positions.back()-positions.front())/(k-1);

    while (right > left + 1)
    {
        max_min_dist = (right+left)/2;
        if (is_spreadable(max_min_dist, k, positions))
            left = max_min_dist;
        else
            right = max_min_dist;
    }

    if (is_spreadable(right, k, positions)) left = right;

    std::cout << left;

}