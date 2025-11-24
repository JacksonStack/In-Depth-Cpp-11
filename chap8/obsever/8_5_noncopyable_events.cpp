class Noncopyable {
protected:
  Noncopyable() = default; 
  ~Noncopyable() = default;
  // forbid copy construct
  Noncopyable(const Noncopyable&) = delete;
  // forbid assign constrct
  Noncopyable& operator=(const Noncopyable&) = delete;
};

#include <iostream>
#include <string>
#include <functional>
#include <map>

using namespace std;

template <typename Func>
class Events : Noncopyable {
public:
  Events() {}
  ~Events() {}

  // register observer, support rr
  int Connect(Func&& f) {
    return Assign(f);
  }

  // register observer
  int Connect(const Func& f) {
    return Assign(f);
  }

  // remove observer
  void Disconnect(int key) {
    m_connection.erase(key);
  }
private:
  std::map<int, Func> m_connection;  // observer list
}
int main() {


    return 0;
}