#include <iostream>

using namespace std;

class A {
public:
    A() : m_ptr(new int(0)) {
        cout << "constructor" << endl;
    }

    A(const A& a) : m_ptr(new int(*a.m_ptr)) {
        cout << "copy constructor" << endl;
    }

    A(A&& a) : m_ptr(a.m_ptr) {
        a.m_ptr = nullptr;
        cout << "move constructor" << endl;
    }

    ~A() {
        cout << "destructor" << endl;
        delete m_ptr;
    }
private:
    int *m_ptr;

};

// to avoid return value optimazation
A Get(bool flag) {
    A a;
    A b;
    if (flag)
        return a;
    else 
        return b;
}

int main() {
    A a = Get(false);

    return 0;
}