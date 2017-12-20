#include <iostream>
#include <iterator>
using namespace std;

template<typename T>
class Range_Iterator {
public:
	using iterator_category = std::input_iterator_tag;
	using value_type = T;
	using difference_type = T;
	using reference = T;
	using pointer = T* const;

	Range_Iterator(T val, T step = 1)
		:cur{val},step{step}
	{}

	Range_Iterator& operator++() {
		cur += step;
		return *this;
	}

	Range_Iterator operator++(int) {
		Range_Iterator temp{*this};
		++*this;
		return temp;
	}

	bool operator==(Range_Iterator const& rhs) const {
		if ( step > 0 ) {
			return cur > rhs.cur;
		} else {
			return cur < rhs.cur;
		}
	}

	bool operator!=(Range_Iterator const& rhs) const {
		return !((*this) == rhs);
	}

	reference operator*() const {
		return cur;
	}

private:
	T cur;
	T step;
};

template <typename T>
class Range {
public:
	using iterator = Range_Iterator<T>;

	Range(T const& start, T const& end, T const& step = 1)
		:starting_value{start},end_value{end},step_size{step} {}
  // Excplicit means compiler can't implicitly use this.
  // However, I am not sure now how this actually works.
  // what does the Range{T{}} mean in this context?
  explicit Range(T end) : Range{T{}, end} {}

	iterator begin() const {
		return Range_Iterator<T>(starting_value,step_size);
	}

	iterator end() const {
		return Range_Iterator<T>(end_value);
	}

private:
	T starting_value;
	T end_value;
	T step_size;
};

// template parameter pack
template<typename T, typename... Args>
auto range(T const& start, Args... args) {
  return Range<T>{start, args...};
}


int main()
{
    {
        // This block should work when everything is finished
        // print values [0,9[
        for ( int v : range(10) )
            cout << v << ' ';

        // print values 2.3, 2.6, 2.9
        for ( auto v : range(2.3, 3.0, 0.3) )
            cout << v << ' ';

        // prints 2 1 0 -1 (has a negative step size)
        for ( auto v : range(2, -2, -1) )
            cout << v << ' ';

        // will not print anything
        for ( auto v : range(2, -1, 3) )
            cout << v << ' ';
    }

    {
        // This block shows some parts of the Range_Iterator class
        Range_Iterator<int> s{2};
        Range_Iterator<int> e{10};
        while ( s != e )
        {
            cout << *s << ' ';
            ++s;
        } // prints 2 3 4 5 6 7 8 9

        // *s = 4; // should not be possible

        Range_Iterator<double> start{2.3, 0.3};
        Range_Iterator<double> stop{3.0};
        while ( start != stop )
        {
            cout << *start++ << ' ';
        } // should print 2.3 2.6 2.9
    }
}
