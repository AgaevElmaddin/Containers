#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <iterator>
#include "iterators_traits.hpp"
#include "is_iterator.hpp"

template <class T>
typename std::enable_if<ft::is_integral<T>::value, void>
f(T)
{
	std::cout << "1\n";
}

void f(int)
{
	std::cout << "2\n";
}

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7};
	auto it = v.begin();
	f(it);
	f(1);
}