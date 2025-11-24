#include <iostream>

using namespace std;

int main()
{
    printf("Hello world!\n");
    auto x = 5;
    // const auto *v = &x, u;
    const auto *v = &x, u = 6;
    // const auto *v = &x, u = 6.0;
    return 0;
}