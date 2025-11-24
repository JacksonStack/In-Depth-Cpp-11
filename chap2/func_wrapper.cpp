#include <iostream>

using namespace std;

template<class Function, class... Args>
inline auto FuncWrapper(Function && f, Args && ... args)->decltype(f(std::forward<Args>(args)...)) {
    return f(std::forward<Args>(args)...);
}

void test0() {
    cout << "void" << endl;
}

int test1() {
    // cout << 1 << endl;
    return 1;
}

int test2(int x) {
    // cout << x << endl;
    return x;    
}

string test3(string s1, string s2) {
    return s1 + s2;
}

void test() {
    FuncWrapper(test0);
    FuncWrapper(test1);
    FuncWrapper(test2, 2);
    FuncWrapper(test3, "aa", "bb");
}

int main() {
    test();
    return 0;
}