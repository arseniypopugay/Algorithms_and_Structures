#include <iostream>
#include <deque>


int main(){

    int N, k;
    char mark;
    std::deque<int> left, right;

    std::cin >> N;

    for (int i=0; i<N; i++){
        std::cin >> mark;

        switch (mark) {
            case '-':
                std::cout << left.front() << std::endl;
                left.pop_front();
                if (right.size()>left.size())
                {
                    left.push_back(right.front());
                    right.pop_front();
                }
                break;
            case '+':
                std::cin >> k;
                right.push_back(k);
                if (right.size()>left.size())
                {
                    left.push_back(right.front());
                    right.pop_front();
                }
                break;
            case '*':
                std::cin >> k;
                right.push_front(k);
                if (right.size()>left.size())
                {
                    left.push_back(right.front());
                    right.pop_front();
                }
                break;
            default:
                break;
        }

    }
}