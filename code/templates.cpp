#include <iostream>

class References {
public:
  References() = default;

  template<class T>
  void fun(T&& x) {
    std::cout << "x: " << x << std::endl;
  }
};

int main() {
  int const i = 42;
  References R;

  R.fun(i); // will call References::fun<int const&>(int const&)
  R.fun(6*7); // will call void References::fun<int>(int&&)
  R.fun(std::move(i)); // will call References::fun<int const>(int const&&)

  return 0;
}
