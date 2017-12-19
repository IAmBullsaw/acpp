# What we learn from going through the exams
In here we go through every exam, and explore the reasoning behind every theory question.
Exams are ordered by date.

## 2017-01-12
>What could be the reasoning behind the STL's function std::adressof when we could just as easily use & to get the adress?

Since it is possible to overload the operator& for user-defined types, this is a way to always be able to get the adress when operator& is overloaded and doesn't supply the actual adress to the object..

> A forwarding reference and an r-value reference are declared in the same way, but are semantically very different. Why?

A forwarding reference is a special template parameter like so:

```c++
template <typename T>
void foo(T&& ref)
{
 // code
}
```

And due to reference collapsing:

```
  A& & becomes A&
  A& && becomes A&
  A&& & becomes A&
  A&& && becomes A&&
```

a forwarding reference will work out whichever type of reference actually got passed in, so an rvalue will behave as an rvalue.

> C++14 added generic lambdas. Give an example of a generic lambda and give a definition of a function object class that is equivalent to the compiler-generated closure object created by your lambda.

A generic lambda is a lambda where at least one parameter is declared `auto`:

```c++
  auto lambda = [](auto a, auto b){ return a * b; }
  cout << lambda(6,7) << " " << lambda(0.4,0.5) << endl;
```

For the above code, a valid generated piece of code would be:

```c++
  struct __NAME {
    template<typename T>
    auto operator()(T a, T b) const { return a * b; }
  }
```

> Why shouldn’t you use operator< when comparing iterators in the code below (container is some sort of STL container):
```
for(auto it = begin(container); it < end(container); ++it )
  // do something with it
```
Only random-access iterators support comparison with operator<. This will not compile with containers that doesn't support random-access. Instead operator!= should be used. (This was answered best from course homepage old_exams answer)



## Sources
### Rvalues
* http://thbecker.net/articles/rvalue_references/section_01.html
