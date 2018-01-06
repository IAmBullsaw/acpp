/*
 * program9.cc          yeah, it probably should be 8...
 */
#include <iostream>
#include <string>
#include "demangle.h"
using namespace std;

template <class C>
class Object_Tracer {
protected:
  Object_Tracer();
  ~Object_Tracer();
};

template <typename T = int>
class Wrapper : public Object_Tracer<Wrapper<T>>
{
public:
  Wrapper(T value = 0) : value_{ value } {}

private:
  T value_;
};

template <class C>
Object_Tracer<C>::Object_Tracer() {
  cout << "Object created: "
    << demangle_name(typeid(C))
    << " ("
    << this
    << ") \n";
}

template <class C>
Object_Tracer<C>::~Object_Tracer() {
  cout << "Object destroyed: "
       << demangle_name(typeid(C))
       << " ("
       << this
       << ") \n";
}

int main()
{
  Wrapper<> wi{ 1 };                  // to be Wrapper<int>

  Wrapper<>* wip = new Wrapper<>{ 2 };  // to be Wrapper<int>*

  Wrapper<double> wd{ 2.3 };

  delete wip;

  Wrapper<char> wch;

  return 0;
}
