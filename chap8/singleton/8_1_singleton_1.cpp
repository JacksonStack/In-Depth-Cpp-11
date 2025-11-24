template <typename T>
class Singleton {
public:
    // for no param
    static T* Instance() {
        if (m_pInstance == nullptr)
            m_pInstance = new T();

        return m_pInstance;
    }

    // for one param
    template<class  T0>
    static T* Instance(T0 arg0) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0);

        return m_pInstance;
    }

    // for two param
    template<class  T0, class T1>
    static T* Instance(T0 arg0, T1 arg1) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0, arg1);

        return m_pInstance;
    }

    // for three param
    template<class  T0, class T1, class T2>
    static T* Instance(T0 arg0, T1 arg1, T2 arg2) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0, arg1, arg2);

        return m_pInstance;
    }

    // for four param
    template<class  T0, class T1, class T2, class T3>
    static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0, arg1, arg2, arg3);

        return m_pInstance;
    }

    // for five param
    template<class  T0, class T1, class T2, class T3, class T4>
    static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0, arg1, arg2, arg3, arg4);

        return m_pInstance;
    }

    // for six param
    template<class  T0, class T1, class T2, class T3, class T4, class T5>
    static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
        if (m_pInstance == nullptr)
            m_pInstance = new T(arg0, arg1, arg2, arg3, arg4, arg5);

        return m_pInstance;
    }

    // get instance
    static T* GetInstance() {
        if (m_pInstance == nullptr)
//            throw std::logic_error("Init first");
            throw "Init first";
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
    A() {}
};

struct B {
    B(int x) {}
};

struct C {
    C(int x, double y) {}
};

int main() {
    Singleton<A>::Instance();
    Singleton<B>::Instance(1);
    Singleton<C>::Instance(1, 3.14);

    Singleton<A>::DestroyInstance();
    Singleton<B>::DestroyInstance();
    Singleton<C>::DestroyInstance();
}