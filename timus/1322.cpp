#include <iostream>

int main() {

    int n;
    std::string s;
    std::cin >> n >> s;

    int count[123] = {0};
    int sum = 0;
    int t[100000] = {0};
    std::string answer(s.length(), ' ');

    for (auto &ch: s) count[ch]++;

    for (int i = 0; i <= 122; i++) {
        sum += count[i];
        count[i] = sum - count[i];
    }

    for (int i = 0; i < s.length(); i++) {
        t[count[s[i]]] = i;
        count[s[i]]++;
    }

    int jump = t[n - 1];
    for (int i = 0; i < s.length(); i++) {
        answer[i] = s[jump];
        jump = t[jump];
    }

    std::cout << answer;
}