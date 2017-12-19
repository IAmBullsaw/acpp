# What we learn from going through the exams
In here I go through every exam, and explore the reasoning behind every theory question.

## 2017-01-12
>What could be the reasoning behind the STL's function std::adressof when we could just as easily use & to get the adress?

Since it is possible to overload the operator& for user-defined types, this is a way to always be able to get the adress when operator& is overloaded and doesn't supply the actual adress to the object..

> A forwarding reference and an r-value reference are declared in the same way, but arre semantically very different. Why?
