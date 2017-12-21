#include <iostream>
#include <string>
#include <iomanip>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Student {
public:
  Student() = default;
  Student(string const& name, string const& surname,
	  string const& pnr, int const& points, 
	  char const& grade)
  :name{name},surname{surname},pnr{pnr},points{points},grade{grade},grade_p{}
  {
    if (grade != 'U') {
      grade_p = grade - '0';
    }
  }

  bool operator<(Student const& stud) const {
    if (grade_p < stud.grade_p) return false;
    else if (grade_p > stud.grade_p) return true;
    else return name+surname < (stud.name+stud.surname);
  }

  string to_string() const {
    ostringstream os;
    os << setw(30) << left << surname + ", " + name 
       << pnr << '\t'
       << grade << ' '
       << '(' << setw(2) << right << points << ')';
    return os.str();
  }

private:
  string name{};
  string surname{};
  string pnr{};
  int points{};
  char grade{};
  int grade_p{};
};

ostream& operator<<(ostream & os, Student const& stud) {
  os << stud.to_string();
  return os;
}

istream& operator>>(istream & is, Student & stud) {
  string name, sur, pnr;
  int points;
  char grade;

  getline(is,name,':');  
  getline(is,sur,':');  
  getline(is,pnr,':');  

  is >> points;
  is.ignore();
  is.get(grade);
  is.ignore();

  stud = Student{name,sur,pnr,points,grade};
  return is;
}

int main() {
  vector<Student> pupils{istream_iterator<Student>{cin},
			 istream_iterator<Student>{}};
  sort(begin(pupils),end(pupils));
  copy(begin(pupils),end(pupils),ostream_iterator<Student>{cout,"\n"}); 
  return 0;
}
