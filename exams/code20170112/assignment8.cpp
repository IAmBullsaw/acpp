#include <iostream>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct HHMM {
  HHMM() = default;
  HHMM(string const& hhmm) {
    int hh = stoi(hhmm.substr(0,2));
    int mm = stoi(hhmm.substr(2,4));
    seconds_ = hh*60*60 + mm*60;
  }

  int seconds() const {return seconds_;}
  int hhmm() const {
    int hh = seconds_/60/60;
    int mm = (seconds_/60)%60;
    return hh*100 + mm;
  }

  bool operator<(HHMM const& rhs) const {
    return seconds_ < rhs.seconds_;
  }

  int seconds_;
};

struct Interval {
  Interval(string const& start, string const& end)
    :start_{start}, end_{end}, interval_{} {
      if (end_ < start_) {
        HHMM day{"2400"};
        HHMM next{};
        next.seconds_ = day.seconds_ + end_.seconds_;
        end_ = next;
      }
      interval_.seconds_ = end_.seconds_ - start_.seconds_;
    }

  bool operator<(Interval const& rhs) const {
    return interval_ < rhs.interval_;
  }

  // Times are in seconds
  HHMM start_;
  HHMM end_;
  HHMM interval_;
};

ostream& operator<<(ostream& os, Interval const& in) {
  os << setfill('0') << setw(4) << right << in.interval_.hhmm();
  return os;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "usage: " << argv[0] << " START_TIME END_TIME" << endl;
    return -1;
  }

  ifstream start_times{argv[1]};
  if (!start_times) {
    cout << "Could't open file: " << argv[1] << " . Please control the file path." << endl;
    return -2;
  }

  ifstream end_times{argv[2]};
  if (!end_times) {
    cout << "Could't open file: " << argv[2] << " . Please control the file path." << endl;
    return -2;
  }

  vector<Interval> intervals;
  transform(istream_iterator<string>{start_times}, istream_iterator<string>{},
            istream_iterator<string>{end_times}, back_inserter(intervals),
            [](string const& start, string const& end) -> Interval {
              return Interval{start,end};
            });
  auto [min, max] = minmax_element(begin(intervals),end(intervals));
  cout << "Largest interval: " << *max << "\nSmallest interval: " << *min << "\nAll intervals" << endl;
  copy(begin(intervals), end(intervals), ostream_iterator<Interval>{cout, "\n"});
  return 0;
}
