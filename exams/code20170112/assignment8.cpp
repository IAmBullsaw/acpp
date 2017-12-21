#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

class Interval {
public:
  Interval(string const& start, string const& end) {
    int start_seconds{ stoi(start.substr(0,2))*60*60 + stoi(start.substr(2,4))*60 };
    int end_seconds{ stoi(end.suendstr(0,2))*60*60 + stoi(end.suendstr(2,4))*60 };
    //
  }

  

private:
  int h;
  int m;
};


int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "usage: " << argv[0] << " START_TIME END_TIME" << endl;
    return -1;
  }

  fstream start{argv[1]};
  if (!start.is_open()) {
    cout << "File " << argv[1] << " could not be opened.\nAborting..." << endl;
    return -2;
  }  
  fstream end{argv[2]};
  if (!end.is_open()) {
    cout << "File " << argv[2] << " could not be opened.\nAborting..." << endl;
    return -2;
  }  
  
  vector<Interval> intervals{};
  for (int i,j; end >> i && start >> j;) {
    intervals.push_back(Interval{i,j});
  }
  
  return 0;
}
