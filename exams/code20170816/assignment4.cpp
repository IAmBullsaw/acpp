#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

struct Policy {
  Policy(bool const& start, bool const& end)
    :start_{start},end_{end}
  {}

  template <typename T>
  bool prefix(T const& t) const {
    return static_cast<bool>(t);
  }

  virtual bool combine(bool const&, bool const&) = 0;
  virtual bool done(bool const& b) const = 0;

  bool start_;
  bool end_;
};

struct All : public Policy {
  All()
    :Policy{true,false}
  {}

  bool combine(bool const& a, bool const& b)  override {
    return a && b;
  }

  bool done(bool const& b)  const override {
    return !b;
  }
};

struct Any : public Policy {
  Any()
    :Policy{false,false}
  {}

  bool combine(bool const& a, bool const& b) override {
    return a || b;
  }

  bool done(bool const& b) const override {
    return b;
  }
};

struct AtLeast : public Policy {
  AtLeast(int const& n)
    :Policy{false,true},n_{n}
  {}

  bool combine(bool const&, bool const& b) override {
    if (b) --n_;
    return false;
  }

  bool done(bool const&) const override {
    return n_ == 0;
  }

  int n_;
};

template <typename Iterator, typename Policy = All>
bool logic_combine(Iterator first,
                   Iterator last,
                   Policy policy = All{}) {
  bool result = policy.start_;

  while (first != last) {
    typename Iterator::value_type const& e{*first};

    auto val{policy.prefix(e)};
    result = policy.combine(result,val);
    if (policy.done(result)) {
      return policy.end_;
    }

    advance(first,1);
  }

  return result;
}

// Main function. The output should be
// true
// false
// false
// true
int main()
{
    std::vector<int> vals {1,1,1,1};
    auto b { begin(vals) };
    auto e { end(vals) };
    using namespace std;
    cout << boolalpha
         << logic_combine(b,e, AtLeast{1}) << '\n'
         << logic_combine(b,e, AtLeast{8}) << '\n'
         << logic_combine(b,e, Any{}) << '\n'
         << logic_combine(b,e) << '\n';
}
