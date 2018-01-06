#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
  using namespace std;
  // 1
  vector<int> numbers {istream_iterator<int>{cin},
                       istream_iterator<int>{}};

  // 2
  cout << numbers.size() << " values read.\n";
  copy(begin(numbers), end(numbers), ostream_iterator<int>{cout," "});

  // 3
  // sorting is fun!
  // sort(rbegin(numbers), rend(numbers));
  sort(begin(numbers), end(numbers), std::greater<int>() );

  // 4
  numbers.erase(unique(begin(numbers),end(numbers)),
                end(numbers));

  // 5
  cout << "\nUnique values in descending order:\n";
  copy(begin(numbers), end(numbers), ostream_iterator<int>{cout," "});

  // 6
  int const n{static_cast<int>(floor(0.05*numbers.size()))};

  // 7
  numbers.erase(begin(numbers),next(begin(numbers),n));
  numbers.erase(prev(end(numbers),n),end(numbers));
  cout << "\nSmallest and largest values removed:\n";
  copy(begin(numbers), end(numbers), ostream_iterator<int>{cout," "});

  // 8
  auto mean{accumulate(begin(numbers),end(numbers),0.0)/numbers.size()};
  cout << "\nMean value: " << setprecision(1) << fixed << mean;

  // 9
  cout << "\nSum of differences: "
       << accumulate(begin(numbers),end(numbers),0.0,[&mean](auto const& sum, auto const& v){
           return sum + abs(mean-v);
         }) << "\n";
}
