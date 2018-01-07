#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <typename T, typename P>
class Wrapper
{
public:
	Wrapper(T const t)
    :value_{t}
  {}
	void set(T const t) {value_ = t;}
	T get() const {return value_;};
	string str() const;
private:
	T value_;
};

template<typename T, typename P>
string Wrapper<T,P>::str() const {return P::convert(value_);}

struct Hexadecimal {
  template <typename T>
  static string convert(T const& t) {
    ostringstream oss{};
    oss << showbase << hex << t;
    return oss.str();
  }
};

struct Quoted {
  template <typename T>
  static string convert(T const& t) {
    ostringstream oss{};
    oss << '\"' << t << "\"";
    return oss.str();
  }
};

int main() {
  Wrapper<int, Hexadecimal> w{4711};
  Wrapper<int, Quoted> w1{4711};
  Wrapper<string, Quoted> w2{"foobar"};
  cout << w.str() << "\n"
       << w1.str() << "\n"
       << w2.str() << "\n";
}
