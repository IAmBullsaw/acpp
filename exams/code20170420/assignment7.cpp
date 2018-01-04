#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
  // 1
  vector<string> words{istream_iterator<string>{cin},istream_iterator<string>{}};
  // 2
  map<string, unsigned, std::less<>> frequency{};
  for_each(begin(words),end(words),
           [&frequency](string word){
             if (auto it = frequency.find(word); it != frequency.end()) {
               ++it->second;
             } else {
               frequency.emplace(word,1);
             }
           });
  // 3
  vector<pair<string,int>> frequencies{make_move_iterator(begin(frequency)), make_move_iterator(end(frequency))};
  sort(begin(frequencies), end(frequencies), [](auto const& a, auto const& b){ return a.second < b.second;});
  // 4
  vector<string> replace{};
  transform(begin(frequencies), next(begin(frequencies),10), begin(replace), [](auto p){return p.first;});
  // 5
  transform(begin(words),end(words),begin(words),[&replace](auto & word){
      if (auto it = find(begin(replace),end(replace),word); it != replace.end()){
        return "$" + to_string(distance(begin(replace),it));
      } else
        return word;
    });
  // 6
  transform(begin(replace), end(replace),ostream_iterator<string>{cout, ";"}, [index=0](auto & word) mutable {
      ostringstream oss;
      oss << '$' << index++ << '=' << word;
      return oss.str();
    });
  // 7
  copy(begin(words),end(words),ostream_iterator<string>{cout, " "});

  return 0;
}
