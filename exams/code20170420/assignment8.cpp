/*
 * program8.cc
 */
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Add and modify stuff according to given specifications.
template <typename T, typename R>
struct Round_Down {
  static T round(R val) {
    return floor(val);
  }
};

template <typename T, typename R>
struct Round_Up {
  static T round(R val) {
    return ceil(val);
  }
};

template <typename T, typename R>
struct Round_Towards_Zero {
  static T round(R val) {
    return (val < 0) ? ceil(val) : floor(val);
  }
};

template <typename T, typename R,
          template<typename,typename> class Policy = Round_Towards_Zero>
class Number
{
public:
  Number(R value = 0.0) : value_(value) {}

  T get_value() const { return value_; }
  void set_value(R value) { value_ = value; }

private:
  T value_;
  T round(R val) {
    return Policy<T,R>::round(val);
  }
};

void test_rounding(double value)
{
  // One object for each of the three rounding policies:
  static Number<int, double, Round_Down> n1;
  static Number<int, double, Round_Up> n2;
  static Number<int, double> n3;

  n1.set_value(value);
  n2.set_value(value);
  n3.set_value(value);

  cout << setw(11) << left << value
       << setw(11) << n1.get_value()
       << setw(11) << n2.get_value()
       << setw(11) << n3.get_value()
       << '\n';
}

int main()
{
  cout << fixed << setprecision(2) << showpos;
  cout << setw(11) << left << "Value"
       << setw(11) << "Down"
       << setw(11) << "Up"
       << setw(11) << "Towards 0"
       << "\n\n";

  test_rounding(9.67);
  test_rounding(9.5);
  test_rounding(9.35);
  test_rounding(9.0);
  test_rounding(0.0);
  test_rounding(-9.0);
  test_rounding(-9.25);
  test_rounding(-9.5);
  test_rounding(-9.67);

  return 0;
}
