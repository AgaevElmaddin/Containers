#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft
{
	// implementation of reverse_iterator
	template <class Iter>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iter>::iterator_category,
						  typename iterator_traits<Iter>::value_type,
						  typename iterator_traits<Iter>::difference_type,
						  typename iterator_traits<Iter>::pointer,
						  typename iterator_traits<Iter>::reference>
	{
		protected:
					// the underlying iterator of which base() returns a copy
					Iter current;
		public:
				// member types
				typedef Iter iterator_type;
				typedef typename std::iterator_traits<Iter>::iterator_category iterator_category;
				typedef typename iterator_traits<Iter>::value_type value_type;
				typedef typename iterator_traits<Iter>::difference_type difference_type;
				typedef typename iterator_traits<Iter>::pointer pointer;
				typedef typename iterator_traits<Iter>::reference reference;

				// member functions
				reverse_iterator(): current(0) {} // default constructor
				explicit reverse_iterator(iterator_type x): current(x) {} // x - iterator to adapt
				template <class U>
				reverse_iterator(const reverse_iterator<U>& copy): current(copy.base()) {} // copy constructor
				~reverse_iterator() {} // destructor

				// assigns another iterator adaptor
				template <class U>
				reverse_iterator& operator=(const reverse_iterator<U>& copy)
				{
					this->current = copy.base();
					return *this;
				}

				//accesses the underlying iterator
				iterator_type base() const
				{
					return this->current;
				}

				// accesses the pointed-to element
				reference operator*() const
				{
					Iter tmp = this->current;
					return *--tmp;
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				// advances or decrements the iterator
				reverse_iterator& operator++()
				{
					--(this->current);
					return *this;
				}

				reverse_iterator operator++(int)
				{
					reverse_iterator tmp(*this);
					--(this->current);
					return tmp;
				}

				reverse_iterator& operator--()
				{
					++(this->current);
					return *this;
				}

				reverse_iterator operator--(int)
				{
					reverse_iterator tmp(*this);
					++(this->current);
					return tmp;
				}

				reverse_iterator operator+(difference_type n) const
				{
					return reverse_iterator(this->current - n);
				}

				reverse_iterator& operator+=(difference_type n)
				{
					this->current -= n;
					return *this;
				}

				reverse_iterator operator-(difference_type n) const
				{
					return reverse_iterator(this->current + n);
				}

				reverse_iterator& operator-=(difference_type n)
				{
					this->current += n;
					return *this;
				}

				// accesses an element by index
				reference operator[](difference_type n) const
				{
					return *(*this + n);
				}
	};

	//Non-member functions
	// compares the underlying iterators
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() == it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() != it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() > it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() >= it2.base();
	}

		template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() < it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it1.base() <= it2.base();
	}

	// advances the iterator
	template <class Iter>
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		return reverse_iterator<Iter>(it.base() - n);
	}

	// computes the distance between two iterator adaptors
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type
	operator-(const reverse_iterator<Iter>& it1, const reverse_iterator<Iter>& it2)
	{
		return it1.base() - it2.base();
	}

	// For case: const_reverse_iterator - reverse_iterator
	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type
	operator-(const reverse_iterator<Iter1>& it1, const reverse_iterator<Iter2>& it2)
	{
		return it2.base() - it1.base();
	}
}

#endif
