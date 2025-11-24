#include <iostream>

using namespace std;

void PrintT(int &t) {
    cout << "lvalue" << endl;
}

template <typename T>
void PrintT(int &t) {
    cout << "rvalue" << endl;
}

template <typename T>
void TestForward(T && v) {
    PrintT(v);
    PrintT(std::forward<T>(v));
    PrintT(std::move(v));
} 

void Test() {
    TestForward(1);
    int x = 1;
    TestForward(x);
    TestForward(std::forward<int>(x));
}

int main() {
    Test();
    return 0;
}