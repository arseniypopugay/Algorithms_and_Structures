#include <iostream>

int main(){
    int a, b, c, d, a_prev;
    int32_t k;
    std::cin >> a >> b >> c >> d >> k;

    for (uint32_t i=0; i<k; i++) {
        a_prev = a;
        a = std::min((a * b - std::min(a * b, c)), d);
//        std::cout << "After " << i << " " << a << std::endl;
        if (!a || a_prev==a)
            break;
    }
    std::cout << a;
}