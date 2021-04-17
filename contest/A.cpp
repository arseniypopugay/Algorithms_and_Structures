#include <iostream>

int main() {
    int n;

    std::cin >> n;

    int current_start = 0,
            best_start = 0, best_end = 0,
            cur_type = 0, prev_type = -1, this_count = 0;


    for (int current_end = 0; current_end < n; current_end++) {
        std::cin >> cur_type;

        if (cur_type == prev_type) {
            this_count++;
            if (this_count == 2) {
                current_start = current_end - 1;
                this_count--;
            }
        } else {

            this_count = 0;
        }

        if (current_end - current_start > best_end - best_start) {
            best_end = current_end;
            best_start = current_start;
        }
        prev_type = cur_type;
    }

    std::cout << best_start + 1 << ' ' << best_end + 1;
}