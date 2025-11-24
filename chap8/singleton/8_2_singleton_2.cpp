#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Singleton {
public:
    template<class... Args>
    static T* Instance(Args&&... args) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(std::forward<Args>(args)...);
        return m_pInstance;
    }

    // get instance
    static T* GetInstance() {
        if (m_pInstance == nullptr)
//            throw std::logic_error("the instance is not init, please initialize the instance first");
            throw std::runtime_error("the instance is not init, please initialize the instance first");
        return m_pInstance;
    }

    // release the instance
    static void DestroyInstance() {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
private:
    // copy or assignment are not allowed
    Singleton(void); 
    virtual ~Singleton(void);
    Singleton(const Singleton&);
    Singleton& operator= (const Singleton);
private:
    static T* m_pInstance;
};

template<class T> T* Singleton<T>::m_pInstance = nullptr;

struct A {
    A(const string&) { cout << "lvalue" << endl; }
    A(string&&) { cout << "rvalue" << endl; }
};

struct B {
    B(const string&) { cout << "lvalue" << endl; }
    B(string&&) { cout << "rvalue" << endl; }
};

struct C {
    C(int x, double y) {}
    void Fun() { cout << "test" << endl; }
};

int main() {
    string str = "bb";

    Singleton<A>::Instance(str);
    // after `move`, str becomes rvalue, using the move semantics to avoid the copy
    Singleton<B>::Instance(std::move(str));
    Singleton<C>::Instance(1, 3.14);
    Singleton<C>::GetInstance()->Fun();

    Singleton<A>::DestroyInstance();
    Singleton<B>::DestroyInstance();
    Singleton<C>::DestroyInstance();
}