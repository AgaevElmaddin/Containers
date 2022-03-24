#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

#include <type_traits>
#include <iterator>

namespace ft
{
	// the iterator_category can be one of these iterator_tags;
	// empty class types used to indicate iterator categories
	struct input_iterator_tag
	{

	};

	struct output_iterator_tag
	{

	};

	struct forward_iterator_tag: public input_iterator_tag
	{

	};

	struct bidirectional_iterator_tag: public forward_iterator_tag
	{

	};

	struct random_access_iterator_tag: public bidirectional_iterator_tag
	{

	};

	// iterator - is the base class provided to simplify definitions of the
	// required types for iterators
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		// the category of the iterator. Must be one of iterator category tags.
		typedef Category iterator_category;

		// the type of the values that can be obtained by dereferencing the iterator
		// This type should be void for output iterators
		typedef T value_type;

		// a type that can be used to identify distance between iterators
		typedef Distance difference_type;

		// defines a pointer to the type iterated over (T)
		typedef Pointer pointer;

		// defines a reference to the type iterated over (T)
		typedef Reference reference;
	};

	// iterator_traits - is a class defining properties of iterators
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	// T* specialization member types
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	 template <class T>
	 struct iterator_traits<const T*>
    {
        /* Result of subtracting one iterator from another. */
        typedef ptrdiff_t                       difference_type;

        /* Type of the element where iterator point. */
        typedef T                               value_type;

        /* Type of a pointer to an element where the iterator point. */
        typedef const T*                        pointer;

        /* Type of a reference where iterator point. */
        typedef const T&                        reference;

        /* The iterator category from Iterator. */
        typedef random_access_iterator_tag  iterator_category;
    };

	// implementation of distance template function;
	// return value - the number of increments needed to go from first to last
	template <class InputIter>
	typename iterator_traits<InputIter>::difference_type
	spec_distance(InputIter first, InputIter last, input_iterator_tag)
	{
		typename iterator_traits<InputIter>::difference_type number_of_steps(0);
		for (; first != last; ++first)
			number_of_steps++;
		return number_of_steps;
	}

	template <class RandomAccessIter>
	typename iterator_traits<RandomAccessIter>::difference_type
	spec_distance(RandomAccessIter first, RandomAccessIter last, random_access_iterator_tag)
	{
		return (last - first);
	}

	template <class Iter>
	typename iterator_traits<Iter>::difference_type
	distance(Iter first, Iter last)
	{
		return spec_distance(first, last, typename iterator_traits<Iter>::iterator_category());
	}

	// implementation of advance template function;
	// increments given iterator "it" by "n" elements
	template <class InputIter>
	void	spec_advance(InputIter& it,
				typename iterator_traits<InputIter>::difference_type n, input_iterator_tag)
	{
		for (; n > 0; --n)
			++it;
	}

	template <class BidirectionalIter>
	void	spec_advance(BidirectionalIter& it,
				typename iterator_traits<BidirectionalIter>::difference_type n, bidirectional_iterator_tag)
	{
		if (n >= 0)
			for (; n > 0; --n)
				++it;
		else
			for (; n < 0; ++n)
				--it;
	}

	template <class RandomAccessIter>
	void	spec_advance(RandomAccessIter& it,
				typename iterator_traits<RandomAccessIter>::difference_type n, random_access_iterator_tag)
	{
		it += n;
	}

	template <class Iter>
	void	advance(Iter& it, typename iterator_traits<Iter>::difference_type n)
	{
		spec_advance(it, n, typename iterator_traits<Iter>::iterator_category());
	}
}

#endif
