#include <iostream>

void bar(int* p) {
    auto l = [p]() {
        std::cout << "*p = " << *p << std::endl;
    };
    l();
}

int main() {
    int a = 10;
    bar(&a);
    std::cout << "a = " << a << std::endl;
    return 0;
}
