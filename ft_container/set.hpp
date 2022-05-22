#ifndef SET_HPP
# define SET_HPP

#include "Red_Black_Tree.hpp"
#include "make_pair.hpp"
#include "Red_Black_Tree_Iterator.hpp"
#include "reverse_iterator.hpp"
#include <functional> // for std::less
#include <memory> // for std::allocator
#include <limits>
#include <algorithm>
#include <cstddef>
#include "lexicographical_compare.hpp"
#include "equal.hpp"

namespace ft
{
	template <class T, class Compare, class Allocator>
	class Red_Black_Tree;

	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
				// member types
				typedef T key_type;
				typedef T value_type;
				typedef Compare key_compare;
				typedef Compare value_compare;
				typedef Alloc allocator_type;
				typedef typename allocator_type::reference reference;
				typedef typename allocator_type::const_reference const_reference;
				typedef typename allocator_type::pointer pointer;
				typedef typename allocator_type::const_pointer const_pointer;
		private:
				typedef Red_Black_Tree<value_type, value_compare, allocator_type> Red_Black_Tree_Type;
				Red_Black_Tree_Type rbt;
		public:
				typedef typename Red_Black_Tree_Type::iterator iterator;
				typedef typename Red_Black_Tree_Type::const_iterator const_iterator;
				typedef typename ft::reverse_iterator<iterator> reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
				typedef typename std::size_t size_type;
				typedef typename std::ptrdiff_t difference_type;

				//**************** member functions: constructor, destructor, operator=, get_allocator ******************//
				//******************************************************************************************************//
				explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
							rbt(comp, alloc) {} // default constructor
				//******************************************************************************************************//

				//******************************************************************************************************//
				template <class InputIterator>
				set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()): rbt(comp, alloc) // range constructor
				{
					insert(first, last);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				set(const set& x): rbt(x.rbt) // copy constructor
				{
					insert(x.begin(), x.end());
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				set& operator=(const set& x) // assignment operator
				{
					if (this == &x)
						return *this;
					rbt.clear();
					//this = rbt(x);
					rbt.cmp = x.rbt.get_value_compare();
					rbt.alloc = x.rbt.get_allocator();
					insert(x.begin(), x.end());
					return *this;
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				~set() // destructor
				{}
				//******************************************************************************************************//

				//******************************************************************************************************//
				allocator_type get_allocator() const // get_allocator
				{
					return rbt.get_allocator();
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
					iterator i = find(value);
					bool exists = 0;

					if (i == end())
					{
						rbt.insert(value);
						exists = 1;
					}
					return pair<iterator, bool>(find(value), exists);
				}

				iterator insert(iterator position, const value_type& value) // hint insert
				{
					(void)position;
					insert(value);
					return find(value);
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
				void swap(set& other) // swap
				{
					rbt.swap(other.rbt);
				}
				//******************************************************************************************************//

				//********************************* member functions: observers ***************************************//
				//******************************************************************************************************//
				key_compare key_comp() const // key_comp
				{
					return rbt.get_value_compare();
				}

				value_compare value_comp() const // value_comp
				{
					return rbt.get_value_compare();
				}
				//******************************************************************************************************//

				//********************************* member functions: operations ***************************************//
				//******************************************************************************************************//
				size_type count(const key_type& key) const // count
				{
					return rbt.count_in_set(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator find(const key_type& key) // find
				{
					return rbt.find_in_set(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				pair<iterator, iterator> equal_range(const key_type& key) // equal_range
				{
					return rbt.equal_range_in_set(key);
				}

				pair<const_iterator, const_iterator> equal_range(const key_type& key) const // equal_range const
				{
					return rbt.equal_range_in_set(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator lower_bound(const key_type& key) // lower_bound
				{
					return rbt.lower_bound_in_set(key);
				}

				const_iterator lower_bound(const key_type& key) const // lower_bound const
				{
					return rbt.lower_bound_in_set(key);
				}
				//******************************************************************************************************//

				//******************************************************************************************************//
				iterator upper_bound(const key_type& key) // upper_bound
				{
					return rbt.upper_bound_in_set(key);
				}

				const_iterator upper_bound(const key_type& key) const // upper_bound const
				{
					return rbt.upper_bound_in_set(key);
				}
				//******************************************************************************************************//
	};
}

#endif
