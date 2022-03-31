#ifndef MAP_HPP
# define MAP_HPP

#include <__tree>
#include <map>
#include "make_pair.hpp"
#include "Red_Black_Tree.hpp"
#include "Red_Black_Tree_Iterator.hpp"
#include "reverse_iterator.hpp"
#include <functional> // for std::less
#include <memory> // for std::allocator
#include <limits>
#include <algorithm>
#include <cstddef>
#include "lexicographical_compare.hpp"
#include "equal.hpp"

// template <class T, class Compare, class Allocator>
// class Red_Black_Tree;

namespace ft
{
	template <class T, class Compare, class Allocator>
	class Red_Black_Tree;

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

				//**************** member functions: constructor, destructor, operator=, get_allocator ******************//
				//******************************************************************************************************//
				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
							rbt(comp, alloc) {} 	// default constructor
				//******************************************************************************************************//

				//******************************************************************************************************//
				template <class InputIterator> // range constructor
				map(InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
						rbt(comp, alloc)
				{
					rbt.insert(first, last);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				map(const map& other): rbt(other.rbt) // copy constructor
				{
					rbt.insert(other.begin(), other.end());
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				~map() // destructor
				{
					rbt.clear();
					rbt.clear_bottom_end();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				map& operator=(const map& other)
				{
					if (this == &other)
						return *this;
					rbt.clear();
					this = rbt(other);
					insert(other.begin(), other.end());
					return *this;
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				allocator_type get_allocator() const // get_allocator
				{
					return rbt.get_allocator();
				}
				//******************************************************************************************************//

				//******************************** member functions: element access ************************************//
				//******************************************************************************************************//
				mapped_type& at(const key_type& key) // at
				{
					iterator it = find(key);
					if (it == rbt.end())
					{
						throw std::out_of_range("map::at: key not found");
					}
					return it->second;
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				mapped_type& operator[](const key_type& key) // operator[]
				{
					iterator it = find(key);
					if (it == rbt.end())
					{
						insert(value_type(key, mapped_type()));
						it = find(key);
					}
					return it->second;
				}
				//******************************************************************************************************//

				//********************************* member functions: iterators ****************************************//
				//******************************************************************************************************//
				iterator begin() // begin
				{
					return rbt.begin();
				}

				const_iterator begin() const // begin const
				{
					return rbt.begin();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator end() // end
				{
					return rbt.end();
				}

				const_iterator end() const // end const
				{
					return rbt.end();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				reverse_iterator rbegin() // rbegin
				{
					return rbt.rbegin();
				}

				const_reverse_iterator rbegin() const // rbegin const
				{
					return rbt.rbegin();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				reverse_iterator rend() // rend
				{
					return rbt.rend();
				}

				const_reverse_iterator rend() const // rend const
				{
					return rbt.rend();
				}
				//******************************************************************************************************//

				//********************************* member functions: capacity *****************************************//
				//******************************************************************************************************//
				bool empty() const // empty
				{
					return rbt.empty();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				size_type size() const // size
				{
					return rbt.size();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				size_type max_size() const // max_size
				{
					return rbt.max_size();
				}
				//******************************************************************************************************//

				//********************************* member functions: modifiers ****************************************//
				//******************************************************************************************************//
				void clear() // clear
				{
					rbt.clear();
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				pair<iterator, bool> insert(const value_type& value) // single element insert
				{
					iterator i = find(value.first);
					bool exists = 0;

					if (i == end())
					{
						rbt.insert(value);
						exists = 1;
					}
					return pair<iterator, bool>(find(value.first), exists);
				}

				iterator insert(iterator position, const value_type& value) // hint insert
				{
					(void)position;
					insert(value);
					return find(value.first);
				}

				template <class InputIterator>
				void insert(InputIterator first, InputIterator last) // range insert
				{
					for(; first != last; ++first)
						insert(*first);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				void erase(iterator position) // single element erase
				{
					rbt.erase(position);
				}

					void erase(iterator first, iterator last) // //erase: [first, last)
				{
					iterator tmp;
					while (first != last)
					{
						tmp = first;
						++first;
						rbt.erase(tmp);
					}
				}

				size_type erase(const key_type& key) // erase key is an element to be removed from the map
				{
					iterator it = find(key);
					if (it == end())
						return 0;
					rbt.erase(it);
					return 1;
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				void swap(map& other) // swap
				{
					rbt.swap(other.rbt);
				}
				//******************************************************************************************************//

				//********************************* member functions: lookup *******************************************//
				//******************************************************************************************************//
				size_type count(const key_type& key) const // count
				{
					return rbt.count(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator find(const key_type& key) // find
				{
					return rbt.find(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				pair<iterator, iterator> equal_range(const key_type& key) // equal_range
				{
					return rbt.equal_range(key);
				}

				pair<const_iterator, const_iterator> equal_range(const key_type& key) const // equal_range const
				{
					return rbt.equal_range(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator lower_bound(const key_type& key) // lower_bound
				{
					return rbt.lower_bound(key);
				}

				const_iterator lower_bound(const key_type& key) const // lower_bound const
				{
					return rbt.lower_bound(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator upper_bound(const key_type& key) // upper_bound
				{
					return rbt.upper_bound(key);
				}

				const_iterator upper_bound(const key_type& key) const // upper_bound const
				{
					return rbt.upper_bound(key);
				}
				//******************************************************************************************************//

				//********************************* member functions: observers ***************************************//
				//******************************************************************************************************//
				key_compare key_comp() const // key_comp
				{
					rbt.get_value_compare();
				}

				value_compare value_comp() const // value_comp
				{
					return value_compare(rbt.get_value_compare());
				}
				//******************************************************************************************************//
		private:
				Red_Black_Tree_Type rbt;
	}; // class map

	//*************************** non-member functions: operator ==, !=. <, <=, >, >= **********************************//
	//*****************************************************************************************************************//
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) // ==
	{
		return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) // !=
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) // <
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) // <=
	{
		return !(x > y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y) // >
	{
		return x < y;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(x < y);
	}
	//*****************************************************************************************************************//
}

#endif
