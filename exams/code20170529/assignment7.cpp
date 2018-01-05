#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
  using namespace std;
  // 1
  vector<string> words{istream_iterator<string>{cin},istream_iterator<string>{}};

  // 2
  cout << words.size() << " words read\n";

  // 3
  for_each(begin(words), end(words),
           [](auto & word) {
             transform(begin(word), end(word), begin(word), ::tolower);
           }
  );

  // 4
  sort(begin(words), end(words));

  // 5
  words.erase(unique(begin(words),end(words)), end(words));

  // 6
  cout << words.size() << " unique words found\n\n";

  // 7
  cout << "The unique words in alphabetical order:\n";
  copy(begin(words),end(words),ostream_iterator<string>{cout," "});

  // 8
  cout << "\n\nThe unique words ordered by length:\n";
  sort(begin(words), end(words),[](auto & a, auto & b) {
      return (a.size() != b.size()) ? (a.size() < b.size()) : (a < b) ;});
  // 9
  copy(begin(words),end(words),ostream_iterator<string>{cout," "});
  cout << "\n";
}
