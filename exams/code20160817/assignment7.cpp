#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

constexpr static int width_ = sizeof("standard deviation")-1;

int main() {
  using namespace std;
  vector<int> numbers{istream_iterator<int>{cin},istream_iterator<int>{}};

  auto mm{minmax_element(begin(numbers),end(numbers))};
  nth_element(begin(numbers),next(begin(numbers),numbers.size()/2),end(numbers));
  auto mean{accumulate(begin(numbers),end(numbers),0.0)/numbers.size()};

  auto stdev{sqrt(accumulate(begin(numbers),end(numbers),0.0, [&mean](auto const& sum, auto const& n){
        return sum + pow(abs(n-mean),2);
      })/numbers.size())};



  cout << setw(width_) << setfill('.') << left
       << "min value" << ": " << *(mm.first) << "\n"
       << setw(width_) << setfill('.') << left
       << "max value" << ": " << *(mm.second) << "\n"
       << setw(width_) << setfill('.') << left
       << "mean" << ": " << mean << "\n"
       << setw(width_) << setfill('.') << left
       << "median" << ": "
       << ((numbers.size() % 2 == 0)? (numbers.at(numbers.size()/2-1) + numbers.at(numbers.size()/2))/2.0 : numbers.at(numbers.size()/2) ) << "\n"
       << setw(width_) << setfill('.') << left
       << "standard deviation" << ": " << stdev << "\n";
}
