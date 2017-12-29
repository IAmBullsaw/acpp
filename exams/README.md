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

## 2017-04-20

> Given the following snippet of code, give a reason for having the using declaration on line 4 instead of qualifying the call on line 5 (i.e. return std::begin(range))

```c++
template <typename Range>
auto iter(Range && range)
{
  using std::begin;
  return begin(range);
}
```

This is because, if you call std::begin(range), Argument-Dependent Lookup (ADL) will not consider user-defined begin().

also:
"The question you might ask yourself now is why that declaration is needed at all, won't ADL take care of calling the correct function anyways? Well most of the time, yes, the problem is the c-style arrays. They are part of the language and not in the std but there is an overload of begin in the library. The using-declaration gives us access to that function." - Facit

> Given the following primary template declaration, give a declaration of a specialization of foo for type char.

```c++
template <typename T>
struct foo;
```

Syntax for template specialization is:
```c++
template <>
struct foo<char>;
```

So this a valid response.

For classes this should give some extra insight:

```c++
namespace N {
    template<class T> class X { /*...*/ }; // primary template
    template<> class X<int> { /*...*/ }; // specialization in same namespace

    template<class T> class Y { /*...*/ }; // primary template
    template<> class Y<double>; // forward declare specialization for double
}
template<>
class N::Y<double> { /*...*/ }; // OK: specialization in same namespace
```


> Assuming v is a std::vector<int>, why is the following code wrong?

```c++
static_assert(v.size() > 0, "vector is empty!");
```

static_assert() needs a boolean expression that is evaluated at compile-time. And `v.size() > 0` will not compile since vector::size is evaluated runtime.

"A contextually converted constant expression of type bool is an expression, contextually converted to bool, where the converted expression is a constant expression and the conversion sequence contains only the conversions above. Such expressions can be used in noexcept specifications and static assert declarations." - cppreference.com

> Assume you have definitions for the following functions:

```c++
void fun(int, short);
void fun(int, double);
```

> The call fun(2,3) will give an ambiguous overload. Why?

Due to implicit conversion the 3 can be seen as either a short or a double.

> Describe what length below does and give a valid example of a call to length.

```c++
template <typename ...Args>
int length(Args && ... args)
{
  return sizeof...(args);
}
```

So, length returns the number of parameters passed.

```c++
  length(1,2,3); // returns 3
  length(4711); // returns 1
  length(); // returns 0
```

## Sources
### ADL
* http://en.cppreference.com/w/cpp/language/adl
### Template specialization
* http://en.cppreference.com/w/cpp/language/template_specialization
### static_assert
* http://en.cppreference.com/w/cpp/language/constant_expression#Converted_constant_expression
