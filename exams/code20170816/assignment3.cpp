#include <vector>
#include <algorithm>
#include <forward_list>
#include <string>
#include <iostream>
#include <iomanip>
template <typename Iterator, typename Comp = std::less<typename Iterator::value_type>>
void ssort(Iterator first, Iterator last, Comp comp = {}) {
  for(Iterator idx{first}; idx != last;++idx) {

    Iterator smallest_at_index{idx};
    Iterator current{idx};
    for (++current; current != last; ++current ) {
      if (comp(*current, *smallest_at_index)) {
        smallest_at_index = current;
      }
    }

    std::iter_swap(smallest_at_index, idx);
  }
}

int main() {

  std::vector<int> v{1,2,4,6,13,6,7};
  std::vector<int> vs{1,2,4,6,6,7,13};

  ssort(begin(v),end(v));

  std::cout << "Sorted vector of ints: ";
  for (auto const& i:v) {std::cout << i << " ";}
  std::cout << "\n";
  std::cout << "Vector is sorted: "<< std::boolalpha << (v == vs) << std::endl;

  std::forward_list <std::string> lst {"hello", "this", "is", "a", "test" };
  std::forward_list <std::string> lsts {"a", "is", "this", "test", "hello" };

  ssort(std::begin(lst), std::end(lst), [](std::string a, std::string b){
          return a.length() < b.length();
        });

  std::cout << "Sorted forward_list of strings: ";
  for (auto const& s: lst) {std::cout << s << " ";}
  std::cout << "\n";
  std::cout << "List is sorted: "<< std::boolalpha << (lst == lsts) << std::endl;
}
