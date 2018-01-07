#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;

template <typename T, typename Container = vector<T>>
class Cycler {
public:
  Cycler(Container & c)
    :c_{c},p_{begin(c)}
  {}

  T& next() {
    T& tmp{*p_};
    if (++p_ == end(c_)) p_ = begin(c_);
    return tmp;
  }
  void reset() { p_ = begin(c_);}
  unsigned size() const {return c_.size();}

private:
  Container& c_;
  typename Container::iterator p_;
};

int main() {
  vector<int> v1{1,2,75,6,7,75,6,7,75,6,7};
  Cycler<int> cycler{v1};
  int loops{20};
  while (loops--) {
    cout << "loop: " << 20 - loops << ": " << cycler.next() << "\n";
  }

  vector<string> v2{"ett","två","tre","fyr","fem","sex"};
  Cycler<string> cycler2{v2};
  loops = 20;
  cout << "\nNever prints \"sex\":\n";
  while (loops--) {
    if (loops % 5 == 0) cycler2.reset();
    cout << "loop: " << 20 - loops << ": " << cycler2.next() << "\n";
  }

  forward_list<string> v3{"jag","är","en","annan","en","container","typ"};
  Cycler<string,forward_list<string>> cycler3{v3};
  loops = 10;
  cout << "\nAnother container type:\n";
  while (loops--) {
    cout << "loop: " << 10 - loops << ": " << cycler3.next() << "\n";
  }


}
