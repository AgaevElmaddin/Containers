#ifndef MAP_HPP
# define MAP_HPP

#include <__tree>
#include <map>
#include "make_pair.hpp"
#include "Red_Black_Tree.hpp"
#include "Red_Black_Tree_Iterator.hpp"
#include "reverse_iterator.hpp"
#include <functional>
#include <memory>
#include <limits>
#include <algorithm>

template <class T, class Compare, class Allocator>
class Red_Black_Tree;

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
				// A typedef for the sort key stored in each element of the map
				typedef Key key_type;
				// A typedef for the data stored in each element of the map
				typedef T mapped_type;
				// A typedef for the type of object stored as an element in a map
				typedef ft::pair<const key_type, mapped_type> value_type;
				// An unsigned integer typedef for the number of elements in a map
				typedef typename std::size_t size_type;
				// A signed integer typedef for the number of elements of a map in a range between elements pointed to by iterators
				typedef typename std::ptrdiff_t difference_type;
				// A typedef for a function object that can compare two sort keys to determine the relative order of two elements in the map
				typedef Compare key_compare;
				// A typedef for the allocator class for the map object
				typedef Allocator allocator_type;
				// A typedef for a reference to an element stored in a map
				typedef value_type& reference;
				// A typedef for a reference to a const element stored in a map for reading and doing const operations
				typedef const value_type& const_reference;
				// A typedef for a pointer to an element in a map
				typedef typename allocator_type::pointer pointer;
				// A typedef for a pointer to a const element in a map
				typedef typename allocator_type::const_pointer const_pointer;
		private:
				typedef Red_Black_Tree<value_type, key_compare, allocator_type> Red_Black_Tree_Type;
		public:
				// A typedef for a bidirectional iterator tha can read or modify any element in a map
				typedef typename Red_Black_Tree_Type::iterator iterator;
				// A typedef for a bidirectional iterator that can read a const element in the map
				typedef typename Red_Black_Tree_Type::const_iterator const_iterator;
				// A typedef for a bidirectional iterator that can read or modify an element in a reversed map
				typedef typename ft::reverse_iterator<iterator> reverse_iterator;
				// A type that provides a bidirectional iterator that can read any const element in the map
				typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

				// member class: compares objects of type value_type.
				class value_compare
				{
					friend class map;
					protected:
								key_compare comp;
								value_compare(key_compare c): comp(c) {}
					public:
							bool operator()(const value_type& x, const value_type& y) const
							{
								return comp(x.first, y.first);
							}
				};

				// member functions: constructor, destructor, operator=, get_allocator
				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
							Red_Black_Tree_Type(comp, alloc) {} 	// default constructor
				// template <class InputIterator> // range constructor
				// map(InputIterator first, InputIterator last,
				// 	const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				// 		Red_Black_Tree_Type(comp, alloc)
				// {

				// }

	};
}

#endif
