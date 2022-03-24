#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

namespace ft
{	// pair
	// couples together a pair of values, which may be different types (T1 and T2).
	template <class T1, class T2>
	struct pair
	{
		// member types
		typedef T1 first_type;
		typedef T2 second_type;

		// member objects
		T1 first;
		T2 second;

		// member functions
		pair(): first(0), second(0) {} // default constructor
		pair(T1 const& t1, T2 const& t2): first(t1), second(t2) {} // constructor with parameters
		template <class U1, class U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second) {} // copy constructor

		pair& operator=(pair const& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}
	};

	// non-member functions
	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first == y.first && x.second == y.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x == y);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return y < x;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(x < y);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
	{
		return !(y < x);
	}

	// make_pair
	// constructs a pair object with its first element set to x and its second element set to y.
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}
}

#endif