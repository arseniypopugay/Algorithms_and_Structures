#include <iostream>
#include <vector>


struct exchange_point {
    int A;
    int B;
    double RAB;
    double CAB;
};

int main() {
    int n, m, s;
    double v;
    double values[101] = {0};

    int a, b;
    double rab, cab, rba, cba;
    std::cin >> n >> m >> s >> v;
    values[s] = v;

    std::vector<exchange_point> points;

    for (int i = 0; i < m; ++i) {
        std::cin >> a >> b >> rab >> cab >> rba >> cba;
        points.push_back({a, b, rab, cab});
        points.push_back({b, a, rba, cba});
    }


    //Алгоритм Форда - Беллмана
    for (int i = 0; i < n - 1; ++i) {
        for (auto &point : points) {
            if (values[point.B] < (values[point.A] - point.CAB) * point.RAB)
                values[point.B] = (values[point.A] - point.CAB) * point.RAB;
        }
    }

    for (auto &point : points) {
        if ((values[point.A] - point.CAB) * point.RAB > values[point.B]) {
            std::cout << "YES";
            return 0;
        }
    }
    std::cout << "NO";
    return 0;
}
