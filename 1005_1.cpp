#include <iostream>

/* вспомогательная функция, возвращающая минимум из модуля первого и второго чисел */
long abs_min(long a, long b) {
    if (a < 0) a = -a;
    if (a < b) return a;
    return b;
}

int main() {
    int n;
    int data[20];
    long sum = 0;
    long min_dif = 100000; //переменная под минимальную разность веса между кучками

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> data[i];
        sum += data[i];
    }

    long limit = 1 << (n - 1); // 2^(n-1)
    for (long k = 0; k < limit; k++) { //накладываем битовую маску, выбираем камни в одну из кучек
        int partial_sum = 0;
        for (int t = 0; t < n - 1; t++) {
            if (k & (1 << t)) { // k & 2^t = наличие t-того бита в записи двоичной записи
                partial_sum += data[t];
            }
        }
        min_dif = abs_min(sum - 2 * partial_sum, min_dif);
        if (min_dif <= 1) { break; } //условия завершение перебора - минимальная разница уже достигнута
    }
    std::cout << min_dif;
}